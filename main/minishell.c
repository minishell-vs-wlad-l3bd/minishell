/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:37:25 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/24 14:21:00 by mohidbel         ###   ########.fr       */
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

void mini_init(t_mini *mini, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_memset(mini, 0, sizeof(t_mini));
	mini->ev = env;
	mini->in = -1;
	mini->out = -1;
	mini->prev_pipe = -1;
	mini->env = env_init(env, 0);
	mini->export_env = env_init(env, 1);
	backup_std_fds(mini);
}

void norm_main(t_mini *mini)
{
	char *str;

	while (1)
	{
		reset_std_fds(mini);
		backup_std_fds(mini);
		str = readline("minishell $ ");
		if (!str)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			reset_std_fds(mini);
			exit(1);
		}
		if (*str && !check_input(str, mini))
			ft_execute(mini, str);
		free(str);
	}
}


int main(int ac, char **av, char **env)
{
	t_mini mini;   

	if (!isatty(STDIN_FILENO))
		return (1);
	disable_echoctl();
	mini_init(&mini, ac, av, env);
	increment_shlvl(&mini);
	setup_parent_signals();
	norm_main(&mini);
	rl_clear_history();
	ft_free_all();
	return 0;
}
