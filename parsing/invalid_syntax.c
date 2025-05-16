#include "../main/minishell.h"

int 	skip_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}
int		invalid_operator(char *str)
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
			continue;
		}
		if (str[i] == '\'' || str[i] == '"')
			i += check_quotes(&str[i]) + 1;
		else
			i++;
	}
	return (0);
}

int		check_redir_sequence(char *str, int *i)
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
int		mixed_redirection_error(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i += check_quotes(&str[i]) + 1;
			continue;
		}
		if (str[i] == '>' || str[i] == '<')
		{
			if (check_redir_sequence(str, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}




int		analys_syntax(char *line)
{
	int		check;

	check = check_syntax(line);
	if (check == 2)
		return (ft_putendl_fd("syntax error: duplicated token", 2), 0);
	if (check == 4)
		return (ft_putendl_fd("syntax error: near unexpected token", 2), 0);
	if (check == 0)
		return (ft_putendl_fd("syntax error: near unexpected token", 2), 0);
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
