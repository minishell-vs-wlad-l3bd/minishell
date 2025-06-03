/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:00:30 by aayad             #+#    #+#             */
/*   Updated: 2025/05/31 10:09:18 by aayad            ###   ########.fr       */
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
	if (start > end)
		return (2);
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

int	analys_syntax(char *line)
{
	int		check;

	check = check_syntax(line);
	if (check == 2)
		return (ft_putendl_fd("syntax error: duplicated token 1", 2), 0);
	if (check == 4)
		return (ft_putendl_fd("syntax error near unexpected token `newline'", 2), 0);
	if (check == 0)
		return (ft_putendl_fd("syntax error: near unexpected token 3", 2), 0);
	if (check == 3)
		return (ft_putendl_fd("syntax error near unexpected token `&'", 2), 0);
	if (check == 5)
		return (ft_putendl_fd("syntax error near unexpected end of line", 2), 0);
	if (redir_syntax_error(line))
		return (ft_putendl_fd("Error", 2), 0);
	if (mixed_redirection_error(line))
		return (ft_putendl_fd("syntax error: parse error nearn 'rederection'", 2), 0);
	return (1);
}
