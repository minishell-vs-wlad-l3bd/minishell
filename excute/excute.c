/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:44 by mohidbel          #+#    #+#             */
/*   Updated: 2025/07/03 15:49:50 by mohidbel         ###   ########.fr       */
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
		do_echo(cmd, mini, head);
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

static void	execute_cmd(char **cmd, t_mini *mini, t_garbege **head)
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

int	check_type(t_mini *mini, int flag, t_garbege **head, t_parsing *parss)
{
	char	*last_file;
	int		fd;
	int		status;

	last_file = NULL;
	if (flag)
	{
		status = handle_heredocs(parss->token, mini, head, &last_file);
		if (status == -1)
			return (0);
	}
	if (last_file && flag)
	{
		fd = open(last_file, O_RDONLY);
		if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
			return (0);
		close(fd);
		unlink(last_file);
	}
	return (handle_all_redirections(parss->token, mini));
}

void	ft_execute(t_mini *mini, t_garbege **head)
{
	char	**paths;

	mini->in = dup(STDIN_FILENO);
	mini->out = dup(STDOUT_FILENO);
	paths = ft_split(get_env_value(mini, "PATH"), ':', head);
	mini->paths = paths;
	if (mini->pipe)
	{
		execute_pipeline(mini, head);
		reset_std_fds(mini);
		return ;
	}
	if (!check_type(mini, 1, head, mini->parss))
	{
		reset_std_fds(mini);
		return ;
	}
	if (is_builtin(mini->parss->cmd[0]))
		execute_builtin(mini->parss->cmd, mini, head);
	else
		execute_cmd(mini->parss->cmd, mini, head);
	reset_std_fds(mini);
}
