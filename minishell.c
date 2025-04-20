#include "minishell.h"

void handler(int sig)
{
	if (sig == SIGINT)
    {
		write(1, "\n", 1);
	    rl_on_new_line();
	    rl_replace_line("", 0);
	    rl_redisplay();
    }
}

int is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
        || !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

void execute_builtin(char **cmd, t_env **env)
{
    quotes(&cmd[1]);
    if (!strcmp(cmd[0], "cd"))
        do_cd(cmd, env);
    else if(!strcmp(cmd[0], "echo"))
        do_echo(&cmd[1]);
    else if (!strcmp(cmd[0], "exit"))
        do_exit(cmd, env);
    else if(!strcmp(cmd[0], "pwd"))
        do_pwd();
    else if(!strcmp(cmd[0], "export"))
        do_export(cmd, env);
    else if(!strcmp(cmd[0], "unset"))
        do_unset(&cmd[1], env);
    else if(!strcmp(cmd[0], "env"))
        do_env(*env);
}

void execute(char **paths, char **cmd)
{
    char *cmd_path = find_cmd_path(paths, cmd[0]);
    if (cmd_path)
    {    
        pid_t pid = fork();
        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            execve(cmd_path, cmd, NULL);
            exit(127);
        }
        waitpid(pid, NULL, 0);
        free(cmd_path);
    }
    else
        printf("minishell: %s: command not found\n", cmd[0]); //strerr ft_putstr_fd
}

int check_is_type(char *str)
{
    if (ft_strncmp(str, "<<", 2) == 0)
        return R_IN; 
    else if (ft_strncmp(str, ">>", 2) == 0)
        return R_APPEND;
    else if (str[0] == '>' && str[1] != '>')
        return R_OUT;
    else if (str[0] == '<' && str[1] != '<')
        return R_IN;
    else if (ft_strchr(str, '|'))
        return R_PIPE;
    else
        return R_NONE;
}


char **split_with_pipes(char *str)
{
    int i = 0;
    char **cmds = ft_split(str, '|');
    while (cmds[i])
    {
        cmds[i] = ft_strtrim(cmds[i], " ");
        i++;
    }
    return cmds;
}

void pipe_handle(char **cmds, char **paths, t_env **env)
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
            handle_redirections(cmd);
            if (is_builtin(cmd[0]))
            {
                execute_builtin(cmd, env);
                exit(0);
            }
            else
            {
                char *cmd_path = find_cmd_path(paths, cmd[0]);
                if (cmd_path)
                execve(cmd_path, cmd, NULL);
                else
                printf("minishell: %s: command not found\n", cmd[0]);
                exit(127);
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

void check_type(char *str, char **paths, t_env *env)
{
    char **cmd = ft_split(str, ' ');
    char **cmds = split_with_pipes(str);

    if(check_is_type(str) == R_PIPE)
        pipe_handle(cmds, paths, &env);
    else
        handle_redirections(cmd);
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char **paths = NULL;
    char **cmd = NULL;
    char *str = NULL;
    t_env *ev = env_init(env);
    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        paths = ft_split(get_env_value(ev, "PATH"), ':');
        str = readline(BLEU"minishell "RESET RED"▶ "RESET);
        if (!str)
        {
            printf("exit\n");
            break ;
        }
        if (!str[0])
        {
            free(str);
            continue ;
        }
        add_history(str);
        cmd = ft_split(str, ' ');
        if (check_is_type(str))
            check_type(str, paths, ev);
        else if (is_builtin(cmd[0]))
            execute_builtin(cmd, &ev);
        else
            execute(paths, cmd);
    }
    rl_clear_history();
    return 0;
}
