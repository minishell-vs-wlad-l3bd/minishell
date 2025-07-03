/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:39 by mohidbel          #+#    #+#             */
/*   Updated: 2025/07/01 15:02:20 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

static int	print_redir_error(char *file, t_mini *mini)
{
	ft_putstr_fd("minishell: ", 2);
	if (file)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	perror("");
	mini->exit = 1;
	return (0);
}

static int	handle_output_redir(t_tokens *token, t_mini *mini)
{
	int	fd;

	fd = open(token->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (print_redir_error(token->file, mini));
	close(fd);
	mini->exit = 0;
	return (1);
}

static int	handle_append_redir(t_tokens *token, t_mini *mini)
{
	int	fd;

	fd = open(token->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (print_redir_error(token->file, mini));
	mini->exit = 0;
	close(fd);
	return (1);
}

static int	handle_input_redir(t_tokens *token, t_mini *mini)
{
	int	fd;

	fd = open(token->file, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putendl_fd("minishell: No such file or directory", 2);
		mini->exit = 1;
		return (0);
	}
	mini->exit = 0;
	close(fd);
	return (1);
}

int	handle_redirections(t_tokens *token, t_mini *mini)
{
	if ((token->output || token->append || token->input)
		&& (!token->file))
	{
		ft_putendl_fd("minishell: No such file or directory", 2);
		mini->exit = 1;
		return (0);
	}
	if (token->output)
		return (handle_output_redir(token, mini));
	else if (token->append)
		return (handle_append_redir(token, mini));
	else if (token->input)
		return (handle_input_redir(token, mini));
	return (1);
}
