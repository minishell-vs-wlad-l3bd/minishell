/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:24:17 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/28 10:01:11 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

void	prepare_heredocs(t_mini *mini, t_garbege **head)
{
	t_parsing	*parss;
	t_tokens	*tokens;

	parss = mini->parss;
	while (parss)
	{
		tokens = parss->token;
		while (tokens)
		{
			if (tokens->heredoc)
			{
				if (parss->heredoc_file)
					unlink(parss->heredoc_file);
				parss->heredoc_file = heredoc(mini, head, tokens);
				if (!parss->heredoc_file)
					return ;
			}
			tokens = tokens->next;
		}
		parss = parss->next;
	}
}

int	fork_failed(t_mini *mini)
{
	close(mini->pipe_in);
	close(mini->pipe_out);
	ft_putendl_fd("minishell: fork failed", 2);
	mini->exit = 1;
	return (0);
}

void	kill_all(pid_t *pids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pids[i] > 0)
			kill(pids[i], SIGKILL);
		i++;
	}
	i = -1;
	while (++i < n)
		waitpid(pids[i], 0, 0);
}

void	handle_empty_redirections(t_parsing *parss)
{
	t_tokens	*tokens;
	int			fd;

	while (parss)
	{
		if (!parss->cmd[0])
		{
			tokens = parss->token;
			while (tokens)
			{
				if (tokens->output)
				{
					fd = open(tokens->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (fd >= 0)
						close(fd);
				}
				else if (tokens->append)
				{
					fd = open(tokens->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (fd >= 0)
						close(fd);
				}
				tokens = tokens->next;
			}
		}
		parss = parss->next;
	}
}
