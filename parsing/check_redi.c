/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:05:49 by aayad             #+#    #+#             */
/*   Updated: 2025/05/31 10:09:59 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

static int	is_invalid_redir(char *str, char c, int *i)
{
	int	count;

	count = 0;
	while (str[*i] == c)
	{
		count++;
		(*i)++;
	}
	if (count > 2)
		return (1);
	while (str[*i] == ' ')
		(*i)++;
	if ((c == '>' && str[*i] == '<') || (c == '<' && str[*i] == '>'))
		return (1);
	return (0);
}

int	redir_syntax_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '>' || str[i] == '<')
		{
			if (is_invalid_redir(str, str[i], &i))
				return (1);
			continue ;
		}
		if (str[i] == '\'' || str[i] == '"')
			i += check_quotes(&str[i]) + 1;
		else
			i++;
	}
	return (0);
}

int	check_redir_sequence(char *str, int *i)
{
	char	c;

	c = str[*i];
	while (str[*i] == c)
	{
		(*i)++;
	}
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '>' || str[*i] == '<')
		return (1);
	return (0);
}

int	mixed_redirection_error(char *str)
{
	int	i;
	int	in_string;

	i = 0;
	in_string = 0;
	while (str[i])
	{
		if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
		{
			in_string = !in_string;
			i++;
			continue ;
		}
		if (!in_string && (str[i] == '>' || str[i] == '<'))
		{
			if (check_redir_sequence(str, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
