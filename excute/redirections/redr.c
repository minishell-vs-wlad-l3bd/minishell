/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:39 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/09 17:08:00 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

int handle_redirections(t_tokens *token, t_mini *mini)
{

    if ((token->output || token->append || token->intput) && !token->file)
    {
        perror("minishell: ");
        return 0;
    }
    if (token->output)
    {
        int fd = open(token->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("minishell: ");
            return 0;
		}
        close(fd);
    }
    else if (token->append)
    {
        int fd = open(token->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("minishell: ");
            return 0;
		}
        close(fd);
    }
    else if (token->intput)
    {
        int fd = open(token->file, O_RDONLY);
        if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
		{
			ft_putendl_fd("minishell: No such file or directory", 2);
            mini->exit = 1;
            return 0;
		}
        close(fd);
    }
    return 1;
}
