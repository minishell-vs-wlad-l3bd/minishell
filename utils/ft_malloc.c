/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:07:16 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/16 21:07:49 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	ft_free_all(t_garbege **head)
{
	t_garbege	*tmp;

	while (*head)
	{
		tmp = *head;
		free((*head)->ptr);
		*head = (*head)->next;
		free(tmp);
	}
	*head = NULL;
}

void	*ft_malloc(size_t size, t_garbege **head)
{
	t_garbege	*new_node;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_free_all(head);
		exit(2);
	}
	new_node = malloc(sizeof(t_garbege));
	if (!new_node)
	{
		free(ptr);
		ft_free_all(head);
		exit(2);
	}
	new_node->ptr = ptr;
	new_node->next = *head;
	*head = new_node;
	return (ptr);
}
