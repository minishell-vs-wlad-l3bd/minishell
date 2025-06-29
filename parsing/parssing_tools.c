/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:18:33 by aayad             #+#    #+#             */
/*   Updated: 2025/06/29 15:57:15 by mohidbel         ###   ########.fr       */
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

int	get_type(char *str)
{
	if (!str)
		return (0);
	return (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>")
		|| !ft_strcmp(str, "<") || !ft_strcmp(str, "<<"));
}

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
