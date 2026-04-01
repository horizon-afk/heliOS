#include "user.h"
#include "math.h"

void main(void)
{
    while (1)
    {
    prompt:
        printf("> ");
        char cmdline[128];
        for (int i = 0;; i++)
        {
            char ch = getchar();
            if (i == sizeof(cmdline) - 1)
            {
                printf("command line too long\n");
                goto prompt;
            }
            else if (ch == '\r')
            {
                printf("\n");
                cmdline[i] = '\0';
                break;
            }
            else if (ch == '\b' || ch == 127)
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
                i--;
            }
            else
            {
                putchar(ch);
                cmdline[i] = ch;
            }
        }
        char stripped[128];
        strip_spaces(stripped, cmdline);

        if (strcmp(stripped, "hello") == 0)
            printf("Hello world from shell!\n");
        else if (strcmp(stripped, "whoami") == 0)
            printf("This is heliOS OS made for RISC-V :)\n");
        else if (strcmp(stripped, "exit") == 0)
            exit();
        else if (is_expr(stripped))
            printf("%d\n", eval_expr(stripped));

        else
            printf("unknown command: %s\n", cmdline);
    }
}
