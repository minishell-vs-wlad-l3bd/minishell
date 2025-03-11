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
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env"))
		return (1);
	return (0);
}
pid_t excuve_fonc(char *path, char **alll)
{
    pid_t i = fork();
    if(i == 0)
        if(execve(path, alll, NULL) == -1)
            exit(1);
    return (i);
}

int main(int ac, char **av, char **env)
{
    char **paths;
    char **cmd;
	 char *path_v;
    ac = 1;
    av = NULL;
    while(1)
    {
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
        paths = ft_split(find_path(env), ':');
        char *str = readline("\033[34mminishell\033[0m \033[31m▶ \033[0m");
		if(!ft_strcmp(str, "exit") || str == NULL)
			exit(1);
		if (!str[0])
			continue;
        cmd = ft_split(str, ' ');
        path_v = find_cmd_path(paths, cmd[0]);
		if (!path_v)
			return (1);
        pid_t n = excuve_fonc(path_v, cmd);
        add_history(str);
        waitpid(n, NULL, 0);
    }
}
