/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:54:28 by aayad             #+#    #+#             */
/*   Updated: 2025/06/15 16:56:21 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	is_inside_single_quotes(char *str, int pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < pos)
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single);
}

int	is_inside_double_quotes(char *str, int pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < pos)
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_double);
}

int	check_quotes_expand(char *str, t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->parss)
		mini->parss->is_expand = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			if (!str[i + 1])
				return (1);
			if (str[i + 1] == '"')
			{
				mini->parss->is_expand = 1;
				return (1);
			}
			if (is_inside_single_quotes(str, i))
				return (1);
			if (is_inside_double_quotes(str, i))
				return (0);
			return (0);
		}
		i++;
	}
	return (0);
}
