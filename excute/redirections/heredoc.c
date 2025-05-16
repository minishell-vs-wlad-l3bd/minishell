#include "../excute.h"

char *get_temp_file(void)
{
    char *file;
    int fd;
    
    file = ft_strjoin("/tmp/heredoc_", ft_itoa(getpid()));
    if (!file)
        return NULL;
        
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return NULL;
    close(fd);
    return file;
}

char *get_delimiter(char *str)
{
    int i = 0;
    char *delimiter = NULL;
    char **tmp = NULL;

    tmp = ft_split(str, ' ');
    if (!tmp)
        return NULL;
        
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

void cleanup_heredoc(t_mini *mini, char *filename, char *delimiter, int fd)
{
    if (filename) {
        unlink(filename);
        free(filename);
    }
    if (delimiter)
        free(delimiter);
    if (fd != -1)
        close(fd);
    signal(SIGINT, handler);
}

void heredoc(t_mini *mini, char *str)
{
    char *filename = NULL;
    char *line = NULL;
    char *delimiter = NULL;
    int fd = -1;
    int input_fd = -1;

    filename = get_temp_file();
    if (!filename) {
        mini->exit = 1;
        return;
    }

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        cleanup_heredoc(mini, filename, NULL, -1);
        mini->exit = 1;
        return;
    }

    delimiter = get_delimiter(str);
    if (!delimiter) {
        cleanup_heredoc(mini, filename, NULL, fd);
        mini->exit = 1;
        return;
    }

    signal(SIGINT, SIG_DFL);
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", STDERR_FILENO);
            break;
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, fd);
        free(line);
	}
    close(fd);
	input_fd = open(filename, O_RDONLY);
	if (input_fd == -1 || dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("minishell: heredoc dup2/read");
		cleanup_heredoc(mini, filename, delimiter, input_fd);
		exit(1);
	}
	close(input_fd);
    unlink(filename);
    signal(SIGINT, handler);
}
