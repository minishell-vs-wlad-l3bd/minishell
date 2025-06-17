/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:37:13 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/15 10:04:03 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	g_check_signal = 0;

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_check_signal = 1;
		rl_redisplay();
	}
}

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

void	setup_parent_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
