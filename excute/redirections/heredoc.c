#include "../excute.h"

int creat_file()
{
	char *file;
	int fd;
	file = ft_strjoin("/tmp/heredoc_", ft_itoa(getpid()));
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return 0;
	return (fd);
}

char *read_line()
{
    char	buffer[2];
	char	*line = ft_strdup("");
	ssize_t	bytes;

	while ((bytes = read(0, buffer, 1)) > 0)
	{
		buffer[bytes] = '\0';
		char *tmp = ft_strjoin(line, buffer);
		free(line);
		line = tmp;
		if (buffer[0] == '\n')
			break;
	}
	return (line);
}

char *get_delimiter(char *str)
{
	int i = 0;
	char *delimiter = NULL;
	char **tmp;

	tmp = ft_split(str, ' ');
	while(tmp[i])
	{
		if(!ft_strcmp(tmp[i], "<<") && tmp[i + 1])
		{
			delimiter = ft_strdup(tmp[i + 1]);
			break;
		}
		i++;
	}
	return delimiter;
}

void heredoc(t_mini *mini, char *str)
{
	int fd;
    char *line;
	char *delimiter;

	fd = creat_file();
	dup2(fd, mini->in);
	delimiter = get_delimiter(str);
	if (!delimiter)
		return ;
	while (1)
	{
		write(1, "> ", 2);
		line = read_line();
		line[ft_strlen(line) - 1] = '\0';
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close (fd);
	close (0);
	free(delimiter);
}
