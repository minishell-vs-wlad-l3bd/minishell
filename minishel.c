#include <libc.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*find_path(char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

char	*find_cmd_path(char **paths, char *cmd)
{
	char	*cmd_p;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
		else
			return (perror("command not found\n"), NULL);
	}
	i = 0;
	while (paths[i])
	{
		cmd_p = ft_strjoin(ft_strdup(paths[i]), "/");
		if (!cmd_p)
			return (NULL);
		cmd_p = ft_strjoin(cmd_p, cmd);
		if (!cmd_p)
			return (NULL);
		if (!access(cmd_p, F_OK | X_OK))
			return (cmd_p);
		free(cmd_p);
		i++;
	}
	return (perror("command not found\n"), NULL);
}

pid_t excuve_fonc(char *path, char **alll)
{
    pid_t i = fork();
    if(i == 0)
    {
        if(execve(path, alll, NULL) == -1)
            exit(1);
    }
    return (i);
}

int main(int ac, char **av, char **env)
{
    char **paths;
    char **cmd;
    while(1)
    {
        paths = ft_split(find_path(env), ':');
        char *str = readline("minishell : ");
        cmd = ft_split(str, ' ');
        char *path_v = find_cmd_path(paths, cmd[0]);
        pid_t n = excuve_fonc(path_v, cmd);
        add_history(str);
        waitpid(n, NULL, 0);
    }
}