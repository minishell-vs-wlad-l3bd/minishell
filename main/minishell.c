/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:37:25 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/21 10:21:19 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backup_std_fds(t_mini *mini)
{
	if (mini->in == -1)
		mini->in = dup(STDIN_FILENO);
	if (mini->out == -1)
		mini->out = dup(STDOUT_FILENO);
	if (mini->in < 0 || mini->out < 0)
		perror("minishell: dup error");
}

void	reset_std_fds(t_mini *mini)
{
	if (mini->in != -1)
	{
		dup2(mini->in, STDIN_FILENO);
		close(mini->in);
		mini->in = -1;
	}
	if (mini->out != -1)
	{
		dup2(mini->out, STDOUT_FILENO);
		close(mini->out);
		mini->out = -1;
	}
}

void	mini_init(t_mini *mini, char **env, t_garbege **head)
{
	ft_memset(mini, 0, sizeof(t_mini));
	mini->ev = env;
	mini->in = -1;
	mini->out = -1;
	mini->prev_pipe = -1;
	mini->pipe_in = -1;
	mini->pipe_out = -1;
	mini->env = env_init(env, 0, head);
	mini->export_env = env_init(env, 1, head);
	backup_std_fds(mini);
}

int	norm_main(t_mini *mini, t_garbege **head, struct termios *term)
{
	char	*str;

	while (1)
	{
		reset_std_fds(mini);
		backup_std_fds(mini);
		str = readline("minishell$ ");
		if (g_check_signal == SIGINT)
		{
			mini->exit = 1;
			g_check_signal = (int)SIG_DFL;
		}
		if (!str)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			reset_std_fds(mini);
			return (mini->exit);
		}
		if (*str && !check_input(str, mini, head))
			ft_execute(mini, head);
		tcsetattr(STDIN_FILENO, TCSANOW, term);
		free(str);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_mini			mini;
	t_garbege		*head;
	int				n;
	struct termios	term;

	n = 0;
	head = NULL;
	(void)ac;
	(void)av;
	if (!isatty(STDIN_FILENO))
		return (1);
	disable_echoctl();
	tcgetattr(STDIN_FILENO, &term);
	mini_init(&mini, env, &head);
	increment_shlvl(&mini, &head);
	setup_parent_signals();
	n = norm_main(&mini, &head, &term);
	ft_free_all(&head);
	rl_clear_history();
	return (n);
}
