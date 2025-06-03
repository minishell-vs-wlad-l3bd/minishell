/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:10:34 by aayad             #+#    #+#             */
/*   Updated: 2025/05/31 10:17:26 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	is_only_spaces(const char *str)
{
	while (*str)
	{
		if (!(*str == ' ' || *str == '\t'))
			return (0);
		str++;
	}
	return (1);
}

int	special_char(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && quote == 0)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		else if (quote == 0 && (line[i] == ';'
				|| line[i] == '\\' || line[i] == '&'))
			return (1);
		i++;
	}
	return (0);
}

int	incorect_quotes(char *line)
{
	int		i;
	char	q;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			q = line[i];
			i++;
			while (line[i] && line[i] != q)
				i++;
			if (!line[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	valid_line(char *line)
{
	if (special_char(line))
		return (ft_putendl_fd("Error : d'ont seport special char", 2), 0);
	if (incorect_quotes(line))
		return (ft_putendl_fd("Error : incorect quotes", 2), 0);
	if (!analys_syntax(line))
		return (0);
	return (1);
}

int	check_input(char *str, t_mini *mini)
{
	if (*str)
		add_history(str);
	if (!*str || is_only_spaces(str))
		return (1);
	if (!valid_line(str))
		return (mini->exit = 258, 1);
	valid_syntax(str, mini);
	if (check_quotes_expand(str, mini))
		return (0);
	if (ft_strchr(str, '$'))
		replace_expand_to_value(mini);
	return (0);
}
