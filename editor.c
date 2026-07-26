#include "main.h"

void init_editor(texteditor *editor)
{
    editor->head = NULL;

    editor->tail = NULL;

    editor->cur_line = NULL;

    editor->cur_lineno = 0;

    editor->cur_pos = 0;
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

void insert_line(texteditor *editor)
{
    printf("enter the line\n");

    char input[MAXLEN];

    scanf(" %[^\n]", input);

    node *new = create_node(input);

    if (!new)
    {
        printf("Memory allocation failed\n");
        return;
    }
    
    if (editor->head == NULL)
    {
        editor->head = new;

        editor->tail = new;

        editor->cur_line = new;

        editor->cur_lineno = 1;

        editor->cur_pos = 0;

        return;
    }
    node *temp = editor->tail;

    temp->next = new;

    new->prev = temp;

    editor->tail = new;

    editor->cur_line = new;
    
    editor->cur_lineno++;

    editor->cur_pos = 0;

    return;
}

void display_editor(texteditor *editor)
{
    if (editor->head == NULL)
    {
        printf("text is empty\n");
        return;
    }

    node *temp =editor->head;

    while (temp)
    {
        printf("%s\n",temp->line);

        temp=temp->next;
    }

}