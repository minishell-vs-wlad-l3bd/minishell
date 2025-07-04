/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:58:50 by aayad             #+#    #+#             */
/*   Updated: 2025/07/03 20:14:32 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

static int	is_in_quotes(char *line, int pos)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (i < pos)
	{
		if ((line[i] == '\'' || line[i] == '\"'))
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		i++;
	}
	return (quote != 0);
}

static int	count_spaces(char *line)
{
	int		i;
	int		extra;

	i = -1;
	extra = 0;
	while (line[++i])
	{
		if ((line[i] == '<' || line[i] == '>') && !is_in_quotes(line, i))
		{
			if (i > 0 && line[i - 1] != ' ' && !is_in_quotes(line, i - 1))
				extra++;
			if ((line[i + 1] == '<' || line[i + 1] == '>')
				&& !is_in_quotes(line, i + 1))
			{
				if (line[i + 2] && line[i + 2] != ' '
					&& !is_in_quotes(line, i + 2))
					extra++;
				i++;
			}
			else if (line[i + 1] && line[i + 1] != ' '
				&& !is_in_quotes(line, i + 1))
				extra++;
		}
	}
	return (extra);
}

char	*add_spaces(char *line, t_garbege **head)
{
	int		i;
	int		j;
	char	*result;

	i = -1;
	j = 0;
	result = ft_malloc(ft_strlen(line) + count_spaces(line) + 1, head);
	while (line[++i])
	{
		if ((line[i] == '<' || line[i] == '>') && !is_in_quotes(line, i))
		{
			if (i > 0 && line[i - 1] != ' ' && !is_in_quotes(line, i - 1))
				result[j++] = ' ';
			result[j++] = line[i];
			if ((line[i + 1] == '<' || line[i + 1] == '>')
				&& !is_in_quotes(line, i + 1))
				result[j++] = line[++i];
			if (line[i + 1] && line[i + 1] != ' '
				&& !is_in_quotes(line, i + 1))
				result[j++] = ' ';
		}
		else
			result[j++] = line[i];
	}
	return ((result[j] = '\0'), result);
}
