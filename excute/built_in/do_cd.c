#include "../excute.h"

void do_cd(char **cmd, t_mini *mini)
{
    char cwd[MAX_PATH];
    char *target = NULL;
    char *error = NULL;
    int print_newdir = 0;

    if (!getcwd(cwd, sizeof(cwd)))
    {
        ft_strlcpy(cwd, get_env_value(mini, "PWD"), MAX_PATH);
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
            check_valid_rdir(target);
        else
        {
            update_env(&mini->env, "OLDPWD", cwd);
            update_env(&mini->export_env, "OLDPWD", cwd);
            update_env(&mini->env, "PWD", getcwd(cwd, sizeof(cwd)));
            update_env(&mini->export_env, "PWD", getcwd(cwd, sizeof(cwd)));
            if (print_newdir)
                if (getcwd(cwd, sizeof(cwd)))
                    printf("%s\n", cwd);
        }
    }
    if (error)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putendl_fd(error, 2);
    }
}
