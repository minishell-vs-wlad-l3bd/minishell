#include "minishell.h"
#include "../excute/excute.h"


void mini_init(t_mini *mini, int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    mini->exit = 0;
    mini->child = 0;
    mini->env = env_init(env, 0);
    mini->export_env = env_init(env, 1);
    mini->in = dup(STDIN_FILENO);
    mini->out = dup(STDOUT_FILENO);
}

void norm_main(t_mini *mini)
{
    char *str;

    while (1)
    {
        str = readline(BLEU"minishell "RESET RED"▶ "RESET);
        if (!str)
        {
            printf("exit\n");
            exit(mini->exit);
        }
        if (str && *str)
            add_history(str);
        else
            continue ;
        signal(SIGINT, handler);
        signal(SIGQUIT, handler);
        ft_execute(mini, str);
    }
}

int main(int ac, char **av, char **env)
{
    t_mini mini;

    if (!isatty(0))
        return (1);
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    mini_init(&mini, ac, av, env);
    norm_main(&mini);
    rl_clear_history();
    return 0;
}
