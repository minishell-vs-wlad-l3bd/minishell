/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:12:08 by aayad             #+#    #+#             */
/*   Updated: 2025/06/17 16:46:05 by aayad            ###   ########.fr       */
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

int	redir_syntax_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
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

int	analys_syntax(char *line, t_mini *mini)
{
	int		check;

	check = check_syntax(line);
	if (check == 4)
		return (ft_putendl_fd("syntax error: near unexpected token", 2),
			mini->exit = 258, 0);
	if (check == 0)
		return (ft_putendl_fd("syntax error: near unexpected token", 2),
			mini->exit = 258, 0);
	if (check == 3)
		return (ft_putendl_fd("syntax error: near unexpected token `&'", 2),
			mini->exit = 258, 0);
	if (check == 5)
		return (ft_putendl_fd("syntax error: near unexpected end of line", 2),
			mini->exit = 258, 0);
	if (redir_syntax_error(line))
		return (ft_putendl_fd("syntax error: invalid redirection", 2),
			mini->exit = 258, 0);
	if (mixed_redirection_error(line))
		return (ft_putendl_fd("syntax error: parse error nearn 'redir'", 2),
			mini->exit = 258, 0);
	return (2);
}
