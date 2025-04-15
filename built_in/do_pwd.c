#include "../minishell.h"

void do_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)))
        printf("%s\n", cwd);
}