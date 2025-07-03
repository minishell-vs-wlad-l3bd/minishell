/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:37:25 by mohidbel          #+#    #+#             */
/*   Updated: 2025/07/03 18:47:42 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_std_fds(t_mini *mini)
{
	close(mini->prev_pipe);
	close(mini->pipe_in);
	close(mini->pipe_out);
	if (mini->in != -1)
	{
		if (dup2(mini->in, STDIN_FILENO) == -1)
			perror("minishell: dup2 stdin error");
		close(mini->in);
		mini->in = -1;
	}
	if (mini->out != -1)
	{
		if (dup2(mini->out, STDOUT_FILENO) == -1)
			perror("minishell: dup2 stdout error");
		close(mini->out);
		mini->out = -1;
	}
}

static int	mini_init(t_mini *mini, char **env, t_garbege **head)
{
	char	*pwd;

	g_check_signal = 0;
	rl_catch_signals = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_putendl_fd("run minishell in correct PATH", 2), 1);
	free(pwd);
	ft_memset(mini, 0, sizeof(t_mini));
	mini->ev = env;
	mini->in = -1;
	mini->out = -1;
	mini->prev_pipe = -1;
	mini->pipe_in = -1;
	mini->pipe_out = -1;
	mini->env = env_init(env, 0, head);
	mini->export_env = env_init(env, 1, head);
	return (0);
}

static int	norm_main(t_mini *mini, t_garbege **head, struct termios *term)
{
	char	*tmp;
	char	*str;

	while (1)
	{
		tmp = readline("minishell$ ");
		if (g_check_signal == SIGINT)
		{
			mini->exit = 1;
			g_check_signal = (int)SIG_DFL;
		}
		if (!tmp)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			return (mini->exit);
		}
		str = ft_strdup(tmp, head);
		free(tmp);
		if (*str && !check_input(str, mini, head))
			ft_execute(mini, head);
		tcsetattr(STDIN_FILENO, TCSANOW, term);
	}
	return (0);
}
// void f(){system("leaks minishell");}

int	main(int ac, char **av, char **env)
{
	t_mini			mini;
	t_garbege		*head;
	int				n;
	struct termios	term;

	// atexit(f);
	(void)av;
	(void)ac;
	n = 0;
	head = NULL;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	tcgetattr(STDIN_FILENO, &term);
	if (mini_init(&mini, env, &head))
		return (1);
	increment_shlvl(&mini, &head);
	setup_parent_signals();
	n = norm_main(&mini, &head, &term);
	ft_free_all(&head);
	rl_clear_history();
	return (n);
}
