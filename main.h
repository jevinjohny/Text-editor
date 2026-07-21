#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#define MAXLEN 1024
typedef struct node
{
    struct node *prev;
    struct node *next;
    char line[MAXLEN];

}node;

typedef struct
{
    node *head;
    node *tail;

    node *cur_line;

    int cur_lineno;
    int cur_pos;

}texteditor;

void init_editor(texteditor *ptr_editor);

#endif