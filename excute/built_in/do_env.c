/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:46 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/09 16:46:06 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"


static void	append_env_line(char **buff, char *key, char *value, t_garbege **head)
{
	char	*line;
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(key, "=", head);
	line = ft_strjoin(tmp, value, head);
	// free(tmp);
	tmp = ft_strjoin(line, "\n", head);
	joined = ft_strjoin(*buff, tmp, head);
	// free(*buff);
	*buff = joined;
}

void	do_env(t_mini *mini, t_garbege **head)
{
	t_env	*node;
	char	*buff;

	node = mini->env;
	buff = ft_strdup("", head);
	while (node)
	{
		if (node->key && node->value)
			append_env_line(&buff, node->key, node->value, head);
		node = node->next;
	}
	printf("%s", buff);
}
