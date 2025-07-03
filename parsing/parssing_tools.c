/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:18:33 by aayad             #+#    #+#             */
/*   Updated: 2025/07/03 17:56:26 by aayad            ###   ########.fr       */
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

char	*return_quote(char **str)
{
	int	i;

	i = 0;
	if (!str || !(*str))
		return (NULL);
	while ((*str)[i])
	{
		if ((*str)[i] == 6)
			(*str)[i] = '\'';
		else if ((*str)[i] == 7)
			(*str)[i] = '"';
		i++;
	}
	return (*str);
}

int	count_heredoc(const char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			count++;
			if (count >= 17)
				return (-1);
			i += 2;
		}
		else
			i++;
	}
	return (count);
}
