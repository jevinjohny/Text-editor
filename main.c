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
        // printf("1. insert new line 2. delete 3. undo 4. redo 5. print 6. move up 7. move down 8. move left 9. move right 10. open 11. save 12. insert text 13. close file 14. copy 15. paste 16. exit 17.backspace\n");

        printf("Text Editor Commands\n");

        scanf("%d", &option);

        char input[MAXLEN];

        switch (option)
        {
        case 1:
        {
            editor.redo_stack.size = 0;
            insert_line(&editor, input_text(input), NORMAL);

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
            move_up(&editor);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 7:
        {
            move_down(&editor);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 8:
        {
            move_left(&editor);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 9:
        {
            move_right(&editor);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 10:
        {
            open_file(&editor);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 11:
        {
            save_file(&editor);

            // system("clear");

            break;
        }
        case 12:
        {
            insert_text(&editor, input_text(input), NORMAL);

            // system("clear");

            display_editor(&editor);

            break;
        }
        case 13:
        {
            close_file(&editor);

            // system("clear");

            display_editor(&editor);

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
            int val;

            while (getchar() != '\n')
                ;

            scanf("%d", &val);

            while (getchar() != '\n')
                ;

            backspace(&editor, val, NORMAL);

            // system("clear");

            display_editor(&editor);
            break;
        }
        }
    }
}