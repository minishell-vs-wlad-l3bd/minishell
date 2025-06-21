/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:08:26 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/17 11:01:43 by mohidbel         ###   ########.fr       */
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

static int	check_error(int flag, char *cmd)
{
	if (flag)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	else
	{
		if (errno == EACCES || errno == ENOTDIR)
		{
			perror("minishell: ");
			return (126);
		}
		else if (errno == ENOENT)
		{
			perror("minishell: ");
			return (127);
		}
	}
	return (1);
}

static char	*build_cmd_path(char *path, char *cmd, t_garbege **head)
{
	char	*tmp;
	char	*cmd_p;

	tmp = ft_strjoin(path, "/", head);
	if (!tmp)
		return (NULL);
	cmd_p = ft_strjoin(tmp, cmd, head);
	if (!cmd_p)
		return (NULL);
	if (access(cmd_p, F_OK | X_OK) == 0)
		return (cmd_p);
	return (NULL);
}

char	*find_cmd_path(char **paths, char *cmd, t_mini *mini, t_garbege **head)
{
	int		i;
	char	*cmd_p;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
			return (mini->exit = check_error(0, cmd), NULL);
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd, head));
		return (mini->exit = check_error(0, cmd), NULL);
	}
	if (!paths)
		return (mini->exit = check_error(1, cmd), NULL);
	i = -1;
	while (paths[++i])
	{
		cmd_p = build_cmd_path(paths[i], cmd, head);
		if (cmd_p)
			return (cmd_p);
	}
	return (mini->exit = check_error(1, cmd), NULL);
}
