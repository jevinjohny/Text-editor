#include <stdio.h>
#define MAXLEN 1024
typedef struct
{
    struct node *head;
    struct node *tail;
    char line[MAXLEN];

}node;

typedef struct
{
    node *head;
    node *tail;

    node *line;

    int lineno;
    int pos;

}texteditor;

void init_editor(texteditor *ptr_editor);