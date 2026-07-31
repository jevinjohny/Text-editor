#include "main.h"

void init_editor(texteditor *editor)
{
    editor->head = NULL;

    editor->tail = NULL;

    editor->cur_line = NULL;

    editor->cur_lineno = 0;

    editor->cur_pos = 0;

    init_stack(&editor->undo_stack);

    init_stack(&editor->redo_stack);
}

node *create_node(const char *text)
{
    node *new = malloc(sizeof(node));

    if (!new)
    {
        return NULL;
    }
    strcpy(new->line, text); // use ncpy

    new->next = NULL;

    new->prev = NULL;

    return new;
}

char *input_text(char *input)
{
    printf("enter the line\n");

    while (getchar() != '\n')
        ;

    fgets(input, MAXLEN, stdin);

    input[strcspn(input, "\n")] = '\0';

    return input;
}

Action record_action(texteditor *editor, const char *text, int operation)
{
    Action action;

    action.cursorLine = editor->cur_lineno;

    action.cursorPos = editor->cur_pos;

    action.operation = operation;

    strcpy(action.text, text);

    return action;
}

void insert_line(texteditor *editor, const char *text, int mode)
{
    node *new = create_node(text);

    if (!new)
    {
        printf("Memory allocation failed\n");
        return;
    }

    if (editor->cur_line == NULL)
    {
        editor->head = new;

        editor->tail = new;

        editor->cur_line = new;

        editor->cur_lineno = 1;

        editor->cur_pos = 0;

        if (mode == NORMAL)
        {
            Action action = record_action(editor, text, INSERT_LINE);

            push(&editor->undo_stack, action);
        }

        return;
    }
    node *temp = editor->cur_line;

    if (temp == editor->tail)
    {
        temp->next = new;

        new->prev = temp;

        editor->tail = new;

        editor->cur_line = new;

        editor->cur_lineno++;

        editor->cur_pos = 0;
    }
    else
    {
        new->next = temp->next;

        temp->next = new;

        new->prev = temp;

        editor->cur_line = new;

        editor->cur_lineno++;

        editor->cur_pos = 0;
    }

    if (mode == NORMAL)
    {
        Action action = record_action(editor, text, INSERT_LINE);

        push(&editor->undo_stack, action);
    }

    return;
}

void undo(texteditor *editor)
{
    if (editor->undo_stack.size == 0)
    {
        printf("Nothing to undo\n");

        return;
    }

    Action action = pop(&editor->undo_stack);

    node *temp = editor->head;

    if (action.operation == INSERT_LINE)
    {
        int i = 1;
        while (temp)
        {
            if (i == action.cursorLine)
            {
                editor->cur_line = temp;

                editor->cur_lineno = action.cursorLine;

                editor->cur_pos = action.cursorPos;

                break;
            }
            temp = temp->next;
            i++;
        }
        delete_line(editor, DNR);

        push(&editor->redo_stack, action);
    }
    else if (action.operation == DELETE_LINE)
    {
        if (action.cursorLine == 1)
        {
            insert_atfirst(editor, action.text);

            push(&editor->redo_stack, action);

            return;
        }
        int i = 1;
        while (temp)
        {
            if (i == action.cursorLine - 1)
            {
                editor->cur_line = temp;

                editor->cur_lineno = action.cursorLine;

                editor->cur_pos = action.cursorPos;

                break;
            }
            temp = temp->next;
            i++;
        }
        insert_line(editor, action.text, DNR);

        editor->cur_lineno = action.cursorLine;

        editor->cur_pos = action.cursorPos;

        push(&editor->redo_stack, action);
    }
}

void insert_atfirst(texteditor *editor, const char *text)
{
    node *new = create_node(text);

    if (!new)
    {
        printf("Memory allocation failed\n");
        return;
    }

    new->next = editor->head;

    if (editor->head != NULL)
    {
        editor->head->prev = new;
    }
    else
    {
        editor->tail = new;
    }

    editor->head = new;

    editor->cur_line = new;

    editor->cur_lineno = 1;

    editor->cur_pos = 0;
}

void redo(texteditor *editor)
{
    if (editor->redo_stack.size == 0)
    {
        printf("Nothing to redo\n");

        return;
    }

    Action action = pop(&editor->redo_stack);

    if (action.operation == INSERT_LINE)
    {
        if (action.cursorLine == 1)
        {
            insert_atfirst(editor, action.text);

            push(&editor->undo_stack, action);

            return;
        }

        node *temp = editor->head;

        int i = 1;
        while (temp)
        {
            if (i == action.cursorLine-1)
            {
                editor->cur_line = temp;

                editor->cur_lineno = action.cursorLine-1;

                editor->cur_pos = action.cursorPos;

                break;
            }
            temp = temp->next;
            i++;
        }
        
        insert_line(editor, action.text, DNR);

        push(&editor->undo_stack, action);
    }
    else if (action.operation == DELETE_LINE)
    {
        node *temp = editor->head;
        int i = 1;

        while (temp)
        {
            if (i == action.cursorLine)
            {
                editor->cur_line = temp;

                editor->cur_lineno = action.cursorLine;

                editor->cur_pos = action.cursorPos;

                delete_line(editor, DNR);

                push(&editor->undo_stack, action);

                return;
            }
            temp = temp->next;

            i++;
        }
        // printf("Redo delete:\n");
        // printf("Stored cursorLine = %d\n", action.cursorLine);
        // printf("Deleting line %d: %s\n",
        //        editor->cur_lineno,
        //        editor->cur_line->line);
    }
}

void insert_text(texteditor *editor, const char *text)
{

    if (editor->cur_line == NULL)
    {
        node *new = create_node(text);

        if (!new)
        {
            printf("Memory allocation failed\n");
            return;
        }

        editor->head = new;

        editor->tail = new;

        editor->cur_line = new;

        editor->cur_lineno = 1;

        editor->cur_pos = 0;

        return;
    }
    node *temp = editor->cur_line;

    int textlen = strlen(text);

    int linelen = strlen(temp->line);

    if (textlen + linelen >= MAXLEN)
    {
        printf("new text is too large to fit inside the line\n");

        return;
    }

    // move everything to right to make space for new text
    memmove((temp->line) + editor->cur_pos + textlen, (temp->line) + editor->cur_pos, linelen - editor->cur_pos + 1);

    // copy to the empty space
    memcpy((temp->line) + editor->cur_pos, text, textlen);

    editor->cur_pos = editor->cur_pos + textlen;

    return;
}

void display_editor(texteditor *editor)
{
    if (editor->head == NULL)
    {
        printf("text is empty\n");
        return;
    }

    node *temp = editor->head;

    int line = 1;

    while (temp)
    {
        if (temp == editor->cur_line)
            printf(">%3d : %s\n", line++, temp->line);
        else
            printf("%4d : %s\n", line++, temp->line);

        temp = temp->next;
    }
    printf("Cursor position : Line %d , coloumn %d\n", editor->cur_lineno, editor->cur_pos);
}

void delete_line(texteditor *editor, int mode)
{
    if (editor->head == NULL)
    {
        printf("text is empty\n");
        return;
    }
    node *temp = editor->cur_line;

    if (mode == NORMAL)
    {
        Action action = record_action(editor, temp->line, DELETE_LINE);

        push(&editor->undo_stack, action);
    }

    if (editor->head == editor->tail)
    {
        free(editor->head);

        editor->head = NULL;

        editor->tail = NULL;

        editor->cur_line = NULL;

        editor->cur_pos = 0;

        editor->cur_lineno = 0;

        return;
    }

    // delete the last line
    if (editor->tail == editor->cur_line)
    {
        (temp->prev)->next = NULL;

        editor->tail = temp->prev;

        editor->cur_line = temp->prev;

        editor->cur_lineno--;

        editor->cur_pos = 0;

        free(temp);
    }
    else if (editor->cur_line == editor->head)
    {
        (temp->next)->prev = NULL;

        editor->head = temp->next;

        editor->cur_line = temp->next;

        editor->cur_lineno = 1;

        editor->cur_pos = 0;

        free(temp);
    }
    else
    {
        (temp->prev)->next = temp->next;

        (temp->next)->prev = temp->prev;

        editor->cur_line = temp->next;

        editor->cur_pos = 0;

        free(temp);
    }
}

void free_editor(texteditor *editor)
{
    node *temp = editor->tail;

    while (temp)
    {
        node *pre = temp->prev;

        free(temp);

        temp = pre;
    }

    free_stack(&editor->undo_stack);

    free_stack(&editor->redo_stack);

    init_editor(editor);
}

void free_stack(DynamicArrayStack *stack)
{
    free(stack->actions);

    stack->actions = NULL;

    stack->size = 0;

    stack->capacity = 0;
}

void move_up(texteditor *editor)
{
    if (editor->cur_lineno >= 2)
    {
        node *temp = editor->cur_line;

        editor->cur_line = temp->prev;

        editor->cur_lineno--;
    }
    display_editor(editor);
}

void move_down(texteditor *editor)
{
    if (editor->cur_line != editor->tail)
    {
        node *temp = editor->cur_line;

        editor->cur_line = temp->next;

        editor->cur_lineno++;
    }
    display_editor(editor);
}

void move_left(texteditor *editor)
{
    if (editor->cur_pos != 0)
    {
        node *temp = editor->cur_line;

        editor->cur_pos--;
    }
    display_editor(editor);
}

void move_right(texteditor *editor)
{
    node *temp = editor->cur_line;

    if (editor->cur_pos != strlen(temp->line) - 1)
    {
        editor->cur_pos++;
    }
    display_editor(editor);
}

void save_file(texteditor *editor)
{
    if (editor->head == NULL)
    {
        printf("Text is empty , Nothing to save\n");
        return;
    }
    FILE *fp = fopen("sample.txt", "w");

    if (fp == NULL)
    {
        printf("file failed to open\n");

        return;
    }
    node *temp = editor->head;

    while (temp)
    {
        fprintf(fp, "%s\n", temp->line);

        temp = temp->next;
    }
    fclose(fp);
    printf("\nFile saved succesfully\n");
}

void open_file(texteditor *editor)
{
    // open the file
    FILE *fp = fopen("sample.txt", "r");

    if (fp == NULL)
    {
        printf("file failed to open\n");

        return;
    }

    // free already allocated memory and initialises
    free_editor(editor);

    // read line by line from the file
    char line[MAXLEN];

    while (fgets(line, MAXLEN, fp))
    {
        line[strcspn(line, "\n")] = '\0';
        // insert using insert line function
        insert_line(editor, line, DNR);
    }
    // close file
    fclose(fp);
}

void close_file(texteditor *editor)
{
    free_editor(editor);

    printf("File closed\n");
}

void copy(texteditor *editor)
{
    if (editor->cur_line == NULL)
    {
        printf("Nothing to copy\n");
        return;
    }
    strcpy(editor->clipboard, (editor->cur_line)->line);
}

void paste(texteditor *editor)
{
    if (strlen(editor->clipboard) == 0)
    {
        printf("Clipboard is empty\n");
        return;
    }
    insert_line(editor, editor->clipboard, DNR);

    display_editor(editor);
}

void init_stack(DynamicArrayStack *stack)
{
    stack->size = 0;

    stack->capacity = 10;

    stack->actions = malloc(stack->capacity * sizeof(Action));

    if (stack->actions == NULL)
    {
        printf("Memory allocations failed\n");
        return;
    }
}

void push(DynamicArrayStack *stack, Action action)
{
    if (stack->size == stack->capacity)
    {
        stack->capacity = stack->capacity * 2;

        Action *temp = realloc(stack->actions, stack->capacity * sizeof(Action));

        if (temp == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }
        stack->actions = temp;
    }

    // insert action at top of the stack
    stack->actions[stack->size] = action;

    stack->size++;
}

Action pop(DynamicArrayStack *stack)
{
    Action action = stack->actions[stack->size - 1];

    stack->size--;

    return action;
}