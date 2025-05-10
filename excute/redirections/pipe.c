#include "../excute.h"

void pipe_handle(char **cmds, char **paths, t_mini *mini)
{
    int count = 0;
    int i = 0;
    
    while (cmds[count])
        count++;
    pid_t *pids = ft_malloc(sizeof(pid_t) * count);
    int (*pipe_fds)[2] = ft_malloc(sizeof(int[2]) * (count - 1));
    while (i < count - 1)
    {
        if (pipe(pipe_fds[i])) {
            perror("pipe failed");
            return;
        }
        i++;
    }
    i = 0;
    while (i < count)
    {
        pids[i] = fork();
        if (pids[i] == 0) 
        {
            if (i > 0)
                dup2(pipe_fds[i-1][0], STDIN_FILENO);
            if (i < count - 1)
                dup2(pipe_fds[i][1], STDOUT_FILENO);
            for (int j = 0; j < count - 1; j++) {
                close(pipe_fds[j][0]);
                close(pipe_fds[j][1]);
            }
            char **cmd = ft_split(cmds[i], ' ');
            if (is_builtin(cmd[0]))
            {
                execute_builtin(cmd, mini);
                mini->exit = 0;
                exit(0);
            }
            else
            {
            	char *cmd_path = find_cmd_path(paths, cmd[0]);
                execve(cmd_path, cmd, NULL);
		        perror("execve failed");
		        mini->exit = 127;
                exit(mini->exit);
            }
        }
        i++;
    }
    for (int i = 0; i < count - 1; i++) {
        close(pipe_fds[i][0]);
        close(pipe_fds[i][1]);
    }
    for (int i = 0; i < count; i++) {
        waitpid(pids[i], NULL, 0);
    }
}
