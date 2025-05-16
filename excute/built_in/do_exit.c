#include "../excute.h"

void do_exit(char **args, t_mini *mini)
{
    int status = 0;
    
    if (args[1])
    {
        status = ft_atoi(args[1]);
        if (status == 0 && !ft_isdigit(args[1][0])) {
            ft_putstr_fd("minishell: exit: numeric argument required\n", STDERR_FILENO);
            status = 2;
        }
    }
    if (mini->in != STDIN_FILENO) close(mini->in);
    if (mini->out != STDOUT_FILENO) close(mini->out);
    
    exit(status);
}
