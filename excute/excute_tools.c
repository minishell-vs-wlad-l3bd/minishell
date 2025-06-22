/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:13:20 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/22 20:34:06 by mohidbel         ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
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

char	*handle_heredocs(t_tokens *tokens, t_mini *mini, t_garbege **head)
{
	char	*last_file;

	last_file = NULL;
	while (tokens)
	{
		if (tokens->heredoc)
		{
			if (last_file)
			{
				unlink(last_file);
				free(last_file);
			}
			last_file = heredoc(mini, head, tokens);
			if (!last_file)
				return (NULL);
		}
		tokens = tokens->next;
	}
	return (last_file);
}

int	handle_all_redirections(t_tokens *tokens, t_mini *mini)
{
	while (tokens)
	{
		if ((tokens->append || tokens->input || tokens->output)
			&& !tokens->heredoc)
		{
			if (!handle_redirections(tokens, mini))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
