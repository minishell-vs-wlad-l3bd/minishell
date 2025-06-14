/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:08:26 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/14 16:43:39 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char	*get_env_value(t_mini *mini, char *key)
{
	t_env	*node;

	node = mini->env;
	if (!node || !key)
		return (NULL);
	while (node)
	{
		if (node->key && !ft_strcmp(node->key, key))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

char	*find_cmd_path(char **paths, char *cmd, t_mini *mini, t_garbege **head)
{
	int		i;
	char	*cmd_p;
	char	*tmp;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
			return (printf("minishell: %s: No such file or directory\n", cmd), mini->exit = 126, NULL);
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd, head));
		return (printf("minishell: %s: Permission denied\n", cmd), mini->exit = 126, NULL);
	}
	if (!paths)
		return (printf("minishell: %s: command not found\n", cmd), mini->exit = 127, NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/", head);
		if (!tmp)
			return (NULL);
		cmd_p = ft_strjoin(tmp, cmd, head);
		if (!cmd_p)
			return (NULL);
		if (access(cmd_p, F_OK | X_OK) == 0)
			return (cmd_p);
	}
	return (printf("minishell: %s: command not found\n", cmd) ,mini->exit = 127, NULL);
}
