/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:57:22 by aayad             #+#    #+#             */
/*   Updated: 2025/06/29 10:33:03 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	count_char(const char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	remove_quotes(char *str)
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

int	check_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	if (!line)
		return (-1);
	if (line[i] == '\'' || line[i] == '"')
	{
		quote = line[i];
		i++;
		while (line[i] && line[i] != quote)
			i++;
		if (!line[i])
			return (-1);
		return (i);
	}
	return (0);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
