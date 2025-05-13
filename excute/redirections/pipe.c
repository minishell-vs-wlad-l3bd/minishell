#include "../excute.h"

int create_pipe(t_mini *mini)
{
    int pipe_fds[2];

    if (pipe(pipe_fds) == -1)
    {
        perror("minishell: pipe failed");
        return 0;
    }
    mini->pipe_in = pipe_fds[0];
    mini->pipe_out = pipe_fds[1];
    return 1;
}

void setup_pipe_io(t_mini *mini, int is_first, int is_last)
{
    if (!is_first)
    {
        dup2(mini->prev_pipe, STDIN_FILENO);
        close(mini->prev_pipe);
    }
    if (!is_last)
        dup2(mini->pipe_out, STDOUT_FILENO);
    close(mini->pipe_in);
    close(mini->pipe_out);
}

char **remove_null_entries(char **cmd)
{
    int count = 0;
    while (cmd[count])
        count++;
    char **new_cmd = ft_calloc(count + 1, sizeof(char *));
    if (!new_cmd)
        return NULL;
    
    int j = 0;
    int i = 0;
    while (cmd[i])
    {
        if (cmd[i] != NULL)
            new_cmd[j++] = ft_strdup(cmd[i]);
        i++;
    }
    new_cmd[j] = NULL;
    for (int i = 0; cmd[i]; i++)
        free(cmd[i]);
    free(cmd);
    return new_cmd;
}

void execute_pipeline(char **cmds, char **paths, t_mini *mini)
{
    int count_cmds = 0;
    mini->prev_pipe = -1;
    int i = -1;

    while (cmds[count_cmds])
        count_cmds++;
    pid_t pids[count_cmds];
    while (++i < count_cmds)
    {
        if (i < count_cmds - 1)
            if (!create_pipe(mini))
                return;
        pids[i] = fork();
        if (pids[i] == 0)
        {
            setup_pipe_io(mini, i == 0, i == count_cmds - 1);
            char **cmd = ft_split(cmds[i], ' ');
            if (!handle_redirections(cmd, mini))
                exit(1);
            cmd = remove_null_entries(cmd);
            if (is_builtin(cmd[0]))
            {
                execute_builtin(cmd, mini);
                exit(0);
            }
            else
            {
                execute_cmd(paths, cmd, mini);
                exit(0);
            }
        }
        else if (pids[i] < 0)
        {
            perror("minishell: fork");
            return;
        }
        if (mini->prev_pipe != -1)
            close(mini->prev_pipe);
        if (i < count_cmds - 1)
        {
            mini->prev_pipe = mini->pipe_in;
            close(mini->pipe_out);
        }
    }
    i = -1;
    while (++i < count_cmds)
        waitpid(pids[i], NULL, 0);
}
