#include "main.h"

int main()
{
    texteditor editor;

    init_editor(&editor);

    int option;

    while (1)
    {
        printf("Text Editor Commands\n");

        printf("1. insert\n2. delete\n3. undo\n4. redo\n5. print\n6. exit\n");

        scanf("%d",&option);

        switch (option)
        {
        case 1:
        {
            insert_line(&editor);
            break;
        }
        case 5:
        {
            display_editor(&editor);
            break;
        }
        case 6:
        {
            return 0;
        }
        }
    }
}