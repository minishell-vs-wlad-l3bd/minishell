#include "../excute.h"

void do_cd(char **cmd, t_mini *mini)
{
    char cwd[MAX_PATH];
    char *target = NULL;
    char *error = NULL;
    int print_newdir = 0;

    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd");
        return;
    }
    if (!cmd[1])
    {
        target = get_env_value(mini, "HOME");
        if (!target)
            error = "HOME not set";
    }
    else if (strcmp(cmd[1], "-") == 0)
    {
        target = get_env_value(mini, "OLDPWD");
        if (!target)
            error = "OLDPWD not set";
        else
            print_newdir = 1;
    }
    else
        target = cmd[1]; 
    if (!error && target)
    {
        if (chdir(target) != 0)
            error = "fail chadir";
        else
        {
            update_env(mini, "OLDPWD", cwd);
            update_env(mini, "PWD", getcwd(cwd, sizeof(cwd)));
            if (print_newdir)
                if (getcwd(cwd, sizeof(cwd)))
                    printf("%s\n", cwd);
        }
    }
    if (error)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(error, 2);
    }
}
