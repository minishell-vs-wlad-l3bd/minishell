/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:44 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/17 11:02:03 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit") || !ft_strcmp(str, "ENV"))
		return (1);
	return (0);
}

void	execute_builtin(char **cmd, t_mini *mini, t_garbege **head)
{
	if (!ft_strcmp(cmd[0], "cd"))
		do_cd(cmd, mini, head);
	else if (!ft_strcmp(cmd[0], "echo"))
		do_echo(mini, head);
	else if (!ft_strcmp(cmd[0], "exit"))
		do_exit(cmd, mini, head);
	else if (!ft_strcmp(cmd[0], "pwd"))
		do_pwd(mini);
	else if (!ft_strcmp(cmd[0], "export"))
		do_export(cmd, mini, head);
	else if (!ft_strcmp(cmd[0], "unset"))
		do_unset(&cmd[1], mini);
	else if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "ENV"))
		do_env(mini, head);
}

void	execute_cmd(char **cmd, t_mini *mini, t_garbege **head)
{
	int		status;
	pid_t	pid;
	char	*cmd_path;

	cmd_path = find_cmd_path(mini->paths, *cmd, mini, head);
	if (!cmd_path)
		return ;
	mini->ev = env_list_to_array(mini->env, head);
	if (is_directory(*cmd))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*cmd, 2);
		return (mini->exit = 126, ft_putstr_fd(": is a directory\n", 2));
	}
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		exec_in_child(cmd_path, cmd, mini);
	else
	{
		waitpid(pid, &status, 0);
		handle_child_status(status, mini);
		setup_parent_signals();
	}
}

int	check_type(t_mini *mini, int flag, t_garbege **head)
{
	char		*last_file;
	t_tokens	*tokens;

	last_file = NULL;
	tokens = mini->parss->token;
	while (tokens)
	{
		if (tokens->heredoc && flag)
		{
			if (!handle_heredoc_token(tokens, mini, head, &last_file))
				return (0);
		}
		tokens = tokens->next;
	}
	return (handle_all_redirections(mini->parss->token, mini));
}

void	ft_execute(t_mini *mini, t_garbege **head)
{
	char	**paths;

	paths = ft_split(get_env_value(mini, "PATH"), ':', head);
	mini->paths = paths;
	if (mini->pipe)
	{
		execute_pipeline(mini, head);
		return ;
	}
	if (!check_type(mini, 1, head))
		return ;
	if (is_builtin(mini->parss->cmd[0]))
		execute_builtin(mini->parss->cmd, mini, head);
	else
		execute_cmd(mini->parss->cmd, mini, head);
}
