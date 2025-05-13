#include "../excute.h"

void do_pwd(t_mini *mini)
{
    char cwd[MAX_PATH];

    if (getcwd(cwd, sizeof(cwd)))
        printf("%s\n", cwd);
    else
        printf("%s\n", get_env_value(mini, "PWD"));
}