#include "main.h"

void init_editor(texteditor *editor)
{
    editor->head = NULL;

    editor->tail = NULL;

    editor->line = NULL;

    editor->lineno = 0;

    editor->pos = 0;
}