/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:14:11 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/16 13:19:07 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

void	wait_for_children(pid_t *pids, int count_cmds, t_mini *mini)
{
	int	i;
	int	status;

	i = -1;
	while (++i < count_cmds)
	{
		waitpid(pids[i], &status, 0);
		handle_child_status(status, mini);
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
