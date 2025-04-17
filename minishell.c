#include "minishell.h"

void handler(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
            signal(SIGINT, handler);
            signal(SIGQUIT, SIG_IGN);
            execve(cmd_path, cmd, NULL);
            exit(127);
        }
        waitpid(pid, NULL, 0);
        free(cmd_path);
    }
    else
    {
        printf("minishell: %s: command not found\n", cmd[0]); //strerr ft_putstr_fd
    }
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
        if (is_builtin(cmd[0]))
            execute_builtin(cmd, &ev);
        else
            execute(paths, cmd);
    }
    rl_clear_history();
    return 0;
}
