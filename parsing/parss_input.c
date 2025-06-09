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
		return (ft_putendl_fd("Error : d'ont seport special char", 2),mini->exit = 1, 0);
	if (incorect_quotes(line))
		return (ft_putendl_fd("Error : incorect quotes", 2),mini->exit = 1, 0);
	if (!analys_syntax(line, mini))
		return (0);
	return (1);
}
int	is_inside_single_quotes(char *str, int pos)
{
	int i;
	int in_single;
	int in_double;

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
	int i;
	int in_single;
	int in_double;

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
	int i;

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

int		check_input(char *str, t_mini *mini, t_garbege **head)
{
	if (*str)
		add_history(str);
	if (!*str || is_only_spaces(str))
		return (1);
	if (!valid_line(str, mini))
		return (mini->exit = 258, 1);
	valid_syntax(str, mini, head);
	return (0);
}
