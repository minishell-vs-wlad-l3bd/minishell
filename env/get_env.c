/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:15:27 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/29 18:15:27 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	update_env(t_env **env, char *key, char *value, t_garbege **head)
{
	size_t	v_len;
	char	*new;
	t_env	*c;

	if (!env || !key || !value)
		return ;
	v_len = ft_strlen(value);
	new = ft_malloc(v_len + 1, head);
	ft_memcpy(new, value, v_len);
	new[v_len] = '\0';
	c = *env;
	while (c)
	{
		if (c->key && !ft_strcmp(c->key, key))
		{
			c->value = new;
			return ;
		}
		c = c->next;
	}
	c = ft_malloc(sizeof(t_env), head);
	c->key = key;
	c->value = new;
	c->next = *env;
	*env = c;
}

static void	env_pre_add(t_env **node, int flg, t_garbege **head)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!flg)
	{
		ft_env_lstadd_back(node,
			ft_env_lstnew("PWD", ft_strdup(cwd, head), head));
		ft_env_lstadd_back(node,
			ft_env_lstnew("SHLVL", ft_strdup("1", head), head));
		ft_env_lstadd_back(node,
			ft_env_lstnew("_", "/usr/bin/env", head));
		ft_env_lstadd_back(node, ft_env_lstnew("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", head));
		free (cwd);
		return ;
	}
	ft_env_lstadd_back(node, ft_env_lstnew("OLDPWD", NULL, head));
	ft_env_lstadd_back(node,
		ft_env_lstnew("PWD", ft_strdup(cwd, head), head));
	ft_env_lstadd_back(node,
		ft_env_lstnew("PATH",
			"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", head));
	ft_env_lstadd_back(node,
		ft_env_lstnew("SHLVL", ft_strdup("1", head), head));
	free (cwd);
}

static int	double_arr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_env	*env_init(char **env, int flag, t_garbege **head)
{
	t_env	*node;
	int		i;
	char	**tmp;

	i = 0;
	node = NULL;
	if (!env || !*env)
	{
		env_pre_add(&node, flag, head);
		return (node);
	}
	while (env[i])
	{
		tmp = ft_split(env[i], '=', head);
		if (double_arr_len(tmp) == 2)
			ft_env_lstadd_back(&node, ft_env_lstnew(tmp[0], tmp[1], head));
		else if (double_arr_len(tmp) == 1)
			ft_env_lstadd_back(&node, ft_env_lstnew(tmp[0], "", head));
		i++;
	}
	return (node);
}
