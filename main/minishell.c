#include "minishell.h"
#include "../excute/excute.h"

void backup_std_fds(t_mini *mini)
{
    if (mini->in == -1)
        mini->in = dup(STDIN_FILENO);
    if (mini->out == -1)
        mini->out = dup(STDOUT_FILENO);
    if (mini->in < 0 || mini->out < 0)
        perror("minishell: dup error");
}

void reset_std_fds(t_mini *mini)
{
    if (mini->in != -1)
    {
        dup2(mini->in, STDIN_FILENO);
        close(mini->in);
        mini->in = -1;
    }
    if (mini->out != -1)
    {
        dup2(mini->out, STDOUT_FILENO);
        close(mini->out);
        mini->out = -1;
    }
}

void mini_init(t_mini *mini, int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    ft_memset(mini, 0, sizeof(t_mini));
    mini->ev = env;
    mini->in = -1;
    mini->out = -1;
    mini->env = env_init(env, 0);
    mini->export_env = env_init(env, 1);
    backup_std_fds(mini);
}

void norm_main(t_mini *mini)
{
    char *str;

    while (1)
    {
        reset_std_fds(mini);
        backup_std_fds(mini);
        str = readline("minishell $ ");
        if (!str)
        {
            ft_putstr_fd("exit\n", STDOUT_FILENO);
            reset_std_fds(mini);
            break;
        }
		if (*str && !check_input(str, mini))
            ft_execute(mini, str);
    }
}
int main(int ac, char **av, char **env)
{
    t_mini mini;

    if (!isatty(0))
        return (1);

    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
    disable_echoctl();
    mini_init(&mini, ac, av, env);
    increment_shlvl(&mini);
    norm_main(&mini);
    rl_clear_history();
    return 0;
}
