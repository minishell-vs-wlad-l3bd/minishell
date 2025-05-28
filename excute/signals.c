/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:37:13 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/24 14:11:58 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int		g_child = 0;

void disable_echoctl(void)
{
	struct termios term;
	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		if (!g_child)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		if (!g_child)
		{
			write(1, "\n", 1);
			exit(1);
		}
	}
}

void setup_parent_signals(void)
{
    g_child = 0;
    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
}

void setup_child_signals(void)
{
    g_child = 1;
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}