/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:12:00 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/28 11:27:20 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

void	ft_sort(t_mini *mini)
{
	t_env	*current;
	t_env	*next_node;
	char	*tmp;

	if (!mini->export_env)
		return ;
	current = mini->export_env;
	while (current)
	{
		next_node = current->next;
		while (next_node)
		{
			if (ft_strcmp(current->key, next_node->key) > 0)
			{
				tmp = current->key;
				current->key = next_node->key;
				next_node->key = tmp;
				tmp = current->value;
				current->value = next_node->value;
				next_node->value = tmp;
			}
			next_node = next_node->next;
		}
		current = current->next;
	}
}

void	print_sort_env(t_mini *mini)
{
	t_env	*node;

	ft_sort(mini);
	node = mini->export_env;
	while (node)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(node->key, 1);
		if (node->value)
			printf("=\"%s\"\n", node->value);
		else
			printf("\n");
		node = node->next;
	}
}

int	check_is_key(t_env **env, char *key)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (1);
		node = node->next;
	}
	return (0);
}
