# include "../main/minishell.h"

int count_char(const char *str, char c)
{
    int count;
	int i;

	i = 0;
	count = 0;
    while (str[i])
	{
        if (str[i] == c)
            count++;
		i++;
	}
    return count;
}

void remove_quotes(char *str)
{
    int remove_single = (count_char(str, '\'') % 2 == 0);
    int remove_double = (count_char(str, '"') % 2 == 0);
    int i = 0;
	int j = 0;
    int in_single = 0;
	int in_double = 0;

    while (str[i])
	{
        if (str[i] == '\'' && !in_double && remove_single)
		{
            in_single = !in_single;
            i++;
        }
        else if (str[i] == '"' && !in_single && remove_double)
		{
            in_double = !in_double;
            i++;
        }
        else
            str[j++] = str[i++];
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

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
