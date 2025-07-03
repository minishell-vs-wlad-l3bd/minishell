/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:14:11 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/30 15:46:50 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

void	wait_for_children(pid_t *pids, int count_cmds, t_mini *mini)
{
	int	i;
	int	status;
	int	sigquit;
	int	sigint;

	i = -1;
	sigquit = 0;
	sigint = 0;
	while (++i < count_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			mini->exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT && !sigquit)
				(ft_putstr_fd("Quit: 3\n", STDERR_FILENO), sigquit = 1);
			else if (WTERMSIG(status) == SIGINT && !sigint)
				(ft_putstr_fd("\n", STDERR_FILENO), sigint = 1);
			mini->exit = 128 + WTERMSIG(status);
		}
	}
}

void	cleanup_heredocs(t_parsing *parss)
{
	while (parss)
	{
		if (parss->heredoc_file)
		{
			unlink(parss->heredoc_file);
			parss->heredoc_file = NULL;
		}
		parss = parss->next;
	}
}

int	ft_lstsize_pipe(t_parsing *parss)
{
	int	i;

	i = 0;
	while (parss)
	{
		i++;
		parss = parss->next;
	}
	return (i);
}

int	create_pipe(t_mini *mini)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe failed");
		return (0);
	}
	mini->pipe_in = pipe_fds[0];
	mini->pipe_out = pipe_fds[1];
	return (1);
}

void	parent_cleanup(t_mini *mini, int i, int total_cmds)
{
	if (mini->prev_pipe != -1)
		close(mini->prev_pipe);
	if (i < total_cmds - 1)
		mini->prev_pipe = mini->pipe_in;
	else
		mini->prev_pipe = -1;
	if (mini->pipe_out != -1)
		close(mini->pipe_out);
}
