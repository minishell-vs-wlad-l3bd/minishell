#include "../main/minishell.h"

int is_only_spaces(const char *str)
{
    while (*str)
    {
        if (!(*str == ' ' || *str == '\t'))
            return 0;
        str++;
    }
    return 1;
}

int		special_char(char *line)
{
	int		i;
	int		skip;

	i = 0;
	while (line[i])
	{
		skip = check_quotes(&line[i]);
		if (skip > 0)
			i += skip;
		else
			if (line[i] == ';' || line[i] == '\\' || line[i] == '&')
				return (1);
		i++;
	}
	return (0);
}

int		incorect_quotes(char *line)
{
	int	i = 0;
	char	q;

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

int		valid_line(char *line)
{
	if (special_char(line))
		return (ft_putendl_fd("Error : d'ont seport special char", 2), 0);
	if (incorect_quotes(line))
		return (ft_putendl_fd("Error : incorect quotes", 2), 0);
	if (!analys_syntax(line))
		return (0);
	return (1);
}

int		check_input(char *str, t_mini *mini)
{
	if (*str)
        add_history(str);
	if (!*str || is_only_spaces(str) || !ft_strncmp(str, ":", 1) || !valid_line(str))
		return (1);
	valid_syntax(str, mini);
	return (0);
}

