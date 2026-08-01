#include "main.h"
#include <stdlib.h>

int main()
{
    texteditor editor;

    init_editor(&editor);

    int option;

    system("clear");

    printf("Text Editor Commands\n");

    while (1)
    {

        // printf("1. insert new line\n2. delete\n3. undo\n4. redo\n5. print\n6. move up\n7. move down\n8. move left\n9. move right\n10. open\n11. save\n12. insert text\n13. close file\n14. copy\n15. paste\n16. exit\n");

        scanf("%d", &option);

        char input[MAXLEN];

        switch (option)
        {
        case 1:
        {
            editor.redo_stack.size = 0;
            insert_line(&editor, input_text(input), NORMAL);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 2:
        {
            editor.redo_stack.size = 0;
            delete_line(&editor, NORMAL);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 3:
        {
            undo(&editor);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 4:
        {
            redo(&editor);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 5:
        {
            // display_editor(&editor);
        }
        case 6:
        {
            move_up(&editor);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 7:
        {
            move_down(&editor);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 8:
        {
            move_left(&editor);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 9:
        {
            move_right(&editor);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 10:
        {
            open_file(&editor);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 11:
        {
            save_file(&editor);

            system("clear");

            break;
        }
        case 12:
        {
            insert_text(&editor, input_text(input));

            system("clear");

            display_editor(&editor);

            break;
        }
        case 13:
        {
            close_file(&editor);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 14:
        {
            copy(&editor);

            system("clear");

            break;
        }
        case 15:
        {
            paste(&editor);

            system("clear");

            display_editor(&editor);

            break;
        }
        case 16:
        {
            free_editor(&editor);

            system("clear");

            display_editor(&editor);

            return 0;
        }
        case 17:
        {
            backspace(&editor, NORMAL);

            system("clear");

            display_editor(&editor);
            break;
        }
        }
    }
}