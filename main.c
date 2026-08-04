#include "main.h"
#include <stdlib.h>

int main()
{
    texteditor editor;

    init_editor(&editor);

    int option;

    system("clear");

    while (1)
    {

        printf("Enter command: ");

        char input[MAXLEN];

        fgets(input, MAXLEN, stdin);

        input[strcspn(input, "\n")] = '\0';

        option = command_handler(input);

        switch (option)
        {
        case 0:
        {
            break;
        }
        case 1:
        {
            editor.redo_stack.size = 0;
            insert_line(&editor, input, NORMAL);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 2:
        {
            editor.redo_stack.size = 0;
            delete_line(&editor, NORMAL);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 3:
        {
            undo(&editor);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 4:
        {
            redo(&editor);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 5:
        {
            display_editor(&editor);
            break;
        }
        case 6:
        {
            int val = atoi(input);

            move_up(&editor, val);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 7:
        {
            int val = atoi(input);

            move_down(&editor, val);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 8:
        {
            int val = atoi(input);

            move_left(&editor, val);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 9:
        {
            int val = atoi(input);

            move_right(&editor, val);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 10:
        {
            open_file(&editor, input);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 11:
        {
            save_file(&editor, input);

            // system("clear");

            break;
        }
        case 12:
        {
            insert_text(&editor, input, NORMAL);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 13:
        {
            close_file(&editor, input);

            // system("clear");

            break;
        }
        case 14:
        {
            copy(&editor);

            // system("clear");

            break;
        }
        case 15:
        {
            paste(&editor);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 16:
        {
            free_editor(&editor);

            // system("clear");

            display_editor(&editor);

            return 0;
        }
        case 17:
        {
            int val = atoi(input);

            backspace(&editor, val, NORMAL);

            // system("clear");

            display_editor(&editor);
            break;
        }
        case 18:
        {
            return 0;
        }
        }
    }
}