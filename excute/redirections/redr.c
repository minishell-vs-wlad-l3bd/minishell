/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:39 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/12 14:18:51 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

int	handle_redirections(t_tokens *token, t_mini *mini)
{
	int	fd;

	if ((token->output || token->append || token->input) && !token->file)
		return (perror("minishell: "), mini->exit = 1, 0);
	if (token->output)
	{
		fd = open(token->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
			return (perror("minishell: "), 0);
		close(fd);
	}
	else if (token->append)
	{
		fd = open(token->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
			return (perror("minishell: "), 0);
		close(fd);
	}
	else if (token->input)
	{
		fd = open(token->file, O_RDONLY);
		if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
		{
			ft_putendl_fd("minishell: No such file or directory", 2);
			return (mini->exit = 1, 0);
		}
		close(fd);
	}
	return (1);
}
