/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:24:17 by mohidbel          #+#    #+#             */
/*   Updated: 2025/07/03 16:41:39 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

int	prepare_heredocs(t_mini *mini, t_garbege **head)
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
					return (0);
			}
			tokens = tokens->next;
		}
		parss = parss->next;
	}
	return (1);
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

void	handle_empty_redirections(t_parsing *parss, t_mini *mini)
{
	t_tokens	*tokens;

	while (parss)
	{
		if (!parss->cmd[0])
		{
			tokens = parss->token;
			if (handle_all_redirections(tokens, mini))
				return ;
		}
		parss = parss->next;
	}
}
