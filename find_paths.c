#include "minishell.h"

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