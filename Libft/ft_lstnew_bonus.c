/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:40:44 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/16 17:03:01 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, t_garbege **head)
{
	t_list	*node1;

	node1 = ft_malloc(sizeof(t_list), head);
	node1->content = content;
	node1->next = NULL;
	return (node1);
}
