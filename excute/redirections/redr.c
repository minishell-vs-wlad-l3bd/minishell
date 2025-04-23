#include "../excute.h"

int handle_redirections(char **cmd)
{
	int i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], ">") && cmd[i + 1])
		{
			int fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror("open"), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			cmd[i] = NULL; 
		}
		else if (!ft_strcmp(cmd[i], ">>") && cmd[i + 1])
		{
			int fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror("open"), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			cmd[i] = NULL;
		}
		else if (!ft_strcmp(cmd[i], "<") && cmd[i + 1])
		{
			int fd = open(cmd[i + 1], O_RDONLY);
			if (fd < 0)
				return (perror("open"), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
			cmd[i] = NULL;
		}
		i++;
	}
	return (0);
}
