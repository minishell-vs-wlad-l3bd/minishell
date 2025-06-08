/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:18:33 by aayad             #+#    #+#             */
/*   Updated: 2025/05/31 10:18:56 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	ft_lstadd_back_2(t_parsing **lst, t_parsing *new)
{
	t_parsing	*tmp;

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

// t_parsing	*ft_lstnew_2(int file, char **cmd, int type)
// {
// 	t_parsing	*node1;

// 	node1 = ft_malloc(sizeof(t_parsing));
// 	if (node1 == NULL)
// 		return (NULL);
// 	node1->cmd = cmd;
// 	node1->file = file;
// 	node1->type = type;
// 	node1->next = NULL;
// 	return (node1);
// }
