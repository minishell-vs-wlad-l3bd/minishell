/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:27 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/29 22:50:09 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

static void	handle_append(t_mini *mini, char *str, t_garbege **head)
{
	char	**parts;
	char	*existing_value;
	char	*new_value;
	char	*key;
	char	*value_part;

	parts = ft_split(str, '+', head);
	if (!parts || !parts[0] || !parts[1])
		return ;
	key = parts[0];
	value_part = parts[1];
	if (value_part[0] != '=')
		return ;
	existing_value = get_env_value(mini, key);
	if (existing_value)
	{
		new_value = ft_strjoin(existing_value, ++value_part, head);
		update_env(&mini->env, key, new_value, head);
		update_env(&mini->export_env, key, new_value, head);
	}
	else
	{
		update_env(&mini->env, key, ++value_part, head);
		update_env(&mini->export_env, key, value_part, head);
	}
}

int	is_valid_env_name(char *name)
{
	char	*p;

	p = name;
	if (!name || !*name)
		return (0);
	if (!ft_isalpha(*p) && *p != '_')
		return (0);
	while (*++p)
	{
		if (!ft_isalnum(*p) && *p != '_')
		{
			if (*p == '=')
				break ;
			if (*p == '+' && *(p + 1) == '=')
				break ;
			return (0);
		}
	}
	return (1);
}

static void	env_add(t_mini *mini, char *s, t_garbege **head)
{
	char	*key;
	char	*value;
	int		key_len;

	if (!is_valid_env_name(s))
		return (mini->exit = 1, ft_putstr_fd("not a valid identifier\n", 2));
	if (ft_strnstr(s, "+=", ft_strlen(s)))
		return (handle_append(mini, s, head));
	if (!ft_strchr(s, '='))
	{
		if (!check_is_key(&mini->export_env, s) && !check_is_key(&mini->env, s))
		{
			ft_env_lstadd_back(&mini->export_env, ft_env_lstnew(s, NULL, head));
			return ;
		}
	}
	if (ft_strchr(s, '='))
	{
		key_len = ft_strchr(s, '=') - s;
		key = ft_malloc(key_len + 1, head);
		ft_strlcpy(key, s, key_len + 1);
		value = ft_strdup(ft_strchr(s, '=') + 1, head);
		update_env(&mini->env, key, value, head);
		update_env(&mini->export_env, key, value, head);
	}
}

void	do_export(char **args, t_mini *mini, t_garbege **head)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!args[1])
		print_sort_env(mini);
	else
	{
		while (args[++i])
		{
			env_add(mini, args[i], head);
			if (mini->exit == 1)
				status = 1;
		}
	}
	mini->exit = status;
}
