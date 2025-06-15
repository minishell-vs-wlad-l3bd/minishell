/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:13:20 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/15 09:49:55 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	is_directory(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

void	exec_in_child(char *cmd_path, char **cmd, t_mini *mini)
{
	setup_child_signals();
	enable_echoctl();
	execve(cmd_path, cmd, mini->ev);
	perror("minishell: ");
	exit(errno);
}

void	handle_child_status(int status, t_mini *mini)
{
	if (WIFEXITED(status))
		mini->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		else if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		mini->exit = 128 + WTERMSIG(status);
	}
}
