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
    node *new=malloc(sizeof(node));

    if (!new)
    {
        printf("Memory allocation failed\n");

        return NULL;
    }
    strcpy(new->line,text);

    new->next=NULL;

    new->prev=NULL;

    return new;
}