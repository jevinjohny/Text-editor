#include "main.h"

int main()
{
    texteditor editor;

    init_editor(&editor);

    int option;

    while (1)
    {
        printf("Text Editor Commands\n");

        printf("1. insert\n2. delete\n3. undo\n4. redo\n5. print\n6. move up\n7. move down\n8. move left\n9. move right\n10. open\n11. save\n12. exit\n");

        scanf("%d", &option);
        
        char input[MAXLEN];

        switch (option)
        {
        case 1:
        {
            insert_text(&editor, input_text(input));
            break;
        }
        case 2:
        {
            delete_line(&editor);
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
            break;
        }
        case 7:
        {
            move_down(&editor);
            break;
        }
        case 8:
        {
            move_left(&editor);
            break;
        }
        case 9:
        {
            move_right(&editor);
            break;
        }
        case 10:
        {
            open_file(&editor);
            break;
        }
        case 11:
        {
            save_file(&editor);
            break;
        }
        case 12:
        {
            free_editor(&editor);
            return 0;
        }
        }
    }
}