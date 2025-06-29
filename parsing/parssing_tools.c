/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:18:33 by aayad             #+#    #+#             */
/*   Updated: 2025/06/29 11:29:33 by aayad            ###   ########.fr       */
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

char	*add_quotes(const char *str, t_garbege **head)
{
	size_t	len;
	char	*quoted;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	quoted = ft_malloc(len + 3, head);
	quoted[0] = '"';
	ft_memcpy(quoted + 1, str, len);
	quoted[len + 1] = '"';
	quoted[len + 2] = '\0';
	return (quoted);
}

void	remove_quotesa(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}
