/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:37:25 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/09 17:15:29 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void backup_std_fds(t_mini *mini)
{
	if (mini->in == -1)
		mini->in = dup(STDIN_FILENO);
	if (mini->out == -1)
		mini->out = dup(STDOUT_FILENO);
	if (mini->in < 0 || mini->out < 0)
		perror("minishell: dup error");
}

void reset_std_fds(t_mini *mini)
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

void mini_init(t_mini *mini, char **env, t_garbege **head)
{
	ft_memset(mini, 0, sizeof(t_mini));
	mini->ev = env;
	mini->in = -1;
	mini->out = -1;
	mini->prev_pipe = -1;
	mini->env = env_init(env, 0, head);
	mini->export_env = env_init(env, 1, head);
	backup_std_fds(mini);
}

void norm_main(t_mini *mini, t_garbege **head)
{
	char *str;

	while (1)
	{
		reset_std_fds(mini);
		backup_std_fds(mini);
		str = readline("minishell$ ");
		if (g_check_signal == 1)
		{
			mini->exit = 1;
			g_check_signal = 0;
		}
		if (!str)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			reset_std_fds(mini);
			break ;
		}
		if (*str && !check_input(str, mini, head))
			ft_execute(mini, head);
		free(str);
	}
}

// void f(){system("leaks minishell");}

int main(int ac, char **av, char **env)
{
	t_mini mini;
	t_garbege *head;
	
	// atexit(f);
	head = NULL;
	(void)ac;
	(void)av;
	if (!isatty(STDIN_FILENO))
		return (1);
	disable_echoctl();
	mini_init(&mini, env, &head);
	increment_shlvl(&mini, &head);
	setup_parent_signals();
	norm_main(&mini, &head);
	ft_free_all(&head);
	rl_clear_history();
	return 0;
}
