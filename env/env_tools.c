/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:15:23 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/29 18:15:23 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	ft_env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}

t_env	*ft_env_lstnew(void *key, void *value, t_garbege **head)
{
	t_env	*node1;

	node1 = ft_malloc(sizeof(t_env), head);
	node1->value = value;
	node1->key = key;
	node1->next = NULL;
	return (node1);
}
