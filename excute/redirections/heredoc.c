/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:25 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/15 10:01:34 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

static char	*get_temp_file(t_garbege **head)
{
	char	*file;
	int		fd;
	char	*pid_str;

	pid_str = ft_itoa(getpid(), head);
	if (!pid_str)
		return (NULL);
	file = ft_strjoin("/tmp/heredoc_", pid_str, head);
	if (!file)
		return (NULL);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	close(fd);
	return (file);
}

static void	heredoc_child_process(int fd, const char *delimiter)
{
	char	*line;

	signal(SIGINT, handler_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			exit(0);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

char	*heredoc(char *delimiter, t_mini *mini, t_garbege **head)
{
	pid_t	pid;
	char	*filename;
	int		fd;
	int		status;

	filename = get_temp_file(head);
	if (!filename || !delimiter)
		return (NULL);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (close(fd), NULL);
	if (pid == 0)
		heredoc_child_process(fd, delimiter);
	close(fd);
	waitpid(pid, &status, 0);
	setup_parent_signals();
	mini->exit = WEXITSTATUS(status);
	return (filename);
}
