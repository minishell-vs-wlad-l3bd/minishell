#include "../excute.h"

int handle_redirections(char **cmd, t_mini *mini)
{
    int i = 0;
    int status = 1;
    
    if (mini->in < 0 || mini->out < 0)
        return (perror("minishell: dup"), -1);

    while (cmd[i] && status == 1)
    {
        if (!ft_strcmp(cmd[i], ">") && cmd[i + 1])
        {
            int fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
			{
				perror("minishell: open");
                status = 0;
			}
            close(fd);
            cmd[i++] = NULL;
            cmd[i] = NULL;
        }
        else if (!ft_strcmp(cmd[i], ">>") && cmd[i + 1])
        {
            int fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
			{
				perror("minishell: open");
                status = 0;
			}
            close(fd);
            cmd[i++] = NULL;
            cmd[i] = NULL;
        }
        else if (!ft_strcmp(cmd[i], "<") && cmd[i + 1])
        {
            int fd = open(cmd[i + 1], O_RDONLY);
            if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
			{
				perror("minishell: open");
                status = 0;
			}
            close(fd);
            cmd[i++] = NULL;
            cmd[i] = NULL;
        }
        else if (cmd[i][0] == '>' || cmd[i][0] == '<')
        {
            ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
            ft_putstr_fd(cmd[i], 2);
            ft_putstr_fd("'\n", 2);
            status = 0;
        }
        else
            i++;
    }
    return status;
}
