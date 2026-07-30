#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1024

typedef struct
{
    int operation;     // Operation type ("insert" or "delete")
    char text[MAXLEN]; // Text involved in the operation
    int cursorLine;    // Line number where operation occurred
    int cursorPos;     // Column position where operation occurred
} Action;

typedef struct
{
    Action *actions; // Dynamic array of actions
    int size;        // Current size of the stack
    int capacity;    // Current capacity of the stack
} DynamicArrayStack;

typedef struct node
{
    struct node *prev;
    struct node *next;
    char line[MAXLEN];

} node;

typedef struct
{
    node *head;
    node *tail;

    node *cur_line;

    int cur_lineno;
    int cur_pos;

    char clipboard[MAXLEN];

    DynamicArrayStack undo_stack;
    DynamicArrayStack redo_stack;

} texteditor;



void init_editor(texteditor *ptr_editor);

void init_stack(DynamicArrayStack *stack);

node *create_node(const char *text);

char *input_text(char *input);

void insert_line(texteditor *editor, const char *text);

void copy(texteditor *editor);

void paste(texteditor *editor);

void insert_text(texteditor *editor, const char *text);

void display_editor(texteditor *editor);

void delete_line(texteditor *editor);

void free_editor(texteditor *editor);

void move_up(texteditor *editor);

void move_down(texteditor *editor);

void move_left(texteditor *editor);

void move_right(texteditor *editor);

void save_file(texteditor *editor);

void open_file(texteditor *editor);

void close_file(texteditor *editor);
#endif