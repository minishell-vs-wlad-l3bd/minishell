/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:36:23 by aayad             #+#    #+#             */
/*   Updated: 2025/06/26 10:48:02 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	skip_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	invalid_operator(char *str)
{
	int		i;
	int		count;

	i = 0;
	while (str && str[i])
	{
		count = 0;
		while (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ' '
			|| str[i] == '&')
		{
			if (str[i] == '|' || str[i] == '&'
				|| ((str[i] == '>' || str[i] == '<') && !count))
				count++;
			i++;
		}
		if (count > 1)
			return (1);
		if (str[i])
			i += check_quotes(&str[i]) + 1;
	}
	return (0);
}

int	check_syntax(char *str)
{
	int	start;
	int	end;

	if (!str)
		return (2);
	start = skip_spaces(str);
	end = ft_strlen(str) - 1;
	while (end > start && str[end] == ' ')
		end--;
	if (str[start] == '|' || invalid_operator(&str[start]))
		return (0);
	if (str[end] == '<' || str[end] == '>')
		return (4);
	if (str[start] == '&' || str[end] == '&')
		return (3);
	if (str[end] == '|' || str[end] == '\\')
		return (5);
	return (1);
}
