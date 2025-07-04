/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:42:53 by aayad             #+#    #+#             */
/*   Updated: 2025/07/03 20:14:55 by aayad            ###   ########.fr       */
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

int	valid_line(char *line, t_mini *mini)
{
	if (special_char(line))
		return (ft_putendl_fd("Error : d'ont seport special char", 2), 0);
	if (incorect_quotes(line))
		return (ft_putendl_fd("Error : incorect quotes", 2), 0);
	if (!analys_syntax(line, mini))
		return (0);
	return (1);
}

int	check_input(char *str, t_mini *mini, t_garbege **head)
{
	if (*str)
		add_history(str);
	if (!*str || is_only_spaces(str))
		return (1);
	if (!valid_line(str, mini))
		return (mini->exit = 258, 1);
	if (count_heredoc(str) == -1)
	{
		ft_putendl_fd("Error to many herdoc", 2);
		ft_free_all(head);
		rl_clear_history();
		exit(2);
	}
	valid_syntax(str, mini, head);
	return (0);
}
