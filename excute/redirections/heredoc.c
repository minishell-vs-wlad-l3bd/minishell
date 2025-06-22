/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:25 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/22 10:06:40 by mohidbel         ###   ########.fr       */
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

static void	heredoc_child_process(int fd, t_mini *mini, t_tokens *tok, t_garbege **head)
{
	char	*line;
	char	*expand;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (tok->here_expand)
			expand = expand_string(line, mini, head);
		if (!line)
			exit(0);
		if (!ft_strcmp(line, tok->file))
		{
			free(line);
			exit(0);
		}
		if (expand)
			ft_putendl_fd(expand, fd);
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
}

char	*heredoc(t_mini *mini, t_garbege **head, t_tokens *tok)
{
	pid_t	pid;
	char	*filename;
	int		fd;
	int		status;

	filename = get_temp_file(head);
	if (!filename || !tok->file)
		return (NULL);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (close(fd), NULL);
	if (pid == 0)
		heredoc_child_process(fd, mini, tok, head);
	close(fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		mini->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		if (WTERMSIG(status) == SIGINT)
			(ft_putstr_fd("\n", STDERR_FILENO), mini->exit = 1);
	return (setup_parent_signals(), filename);
}
