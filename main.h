#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
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

node *create_node(const char *text);

void insert_line(texteditor *editor);

void display_editor(texteditor *editor);

void delete_line(texteditor *editor);

#endif