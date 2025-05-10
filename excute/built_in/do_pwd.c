#include "../excute.h"

void do_pwd(void)
{
    char cwd[MAX_PATH];

    if (getcwd(cwd, sizeof(cwd)))
        printf("%s\n", cwd);
}