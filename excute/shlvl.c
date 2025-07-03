/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:37:07 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/30 18:02:28 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char	**env_list_to_array(t_env *env, t_garbege **head)
{
	int		i;
	int		count;
	char	**arr;
	char	*key_equal;
	t_env	*tmp;

	tmp = env;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = (char **)ft_malloc(sizeof(char *) * (count + 1), head);
	tmp = env;
	i = 0;
	while (tmp)
	{
		key_equal = ft_strjoin(tmp->key, "=", head);
		arr[i] = ft_strjoin(key_equal, tmp->value, head);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	increment_shlvl(t_mini *mini, t_garbege **head)
{
	int		shlvl;
	char	*shlvl_value;

	shlvl_value = get_env_value(mini, "SHLVL");
	shlvl = ft_atoi(shlvl_value) + 1;
	update_env(&mini->env, "SHLVL", ft_itoa(shlvl, head), head);
	update_env(&mini->export_env, "SHLVL", ft_itoa(shlvl, head), head);
	mini->ev = env_list_to_array(mini->env, head);
}
