# include "../main/minishell.h"

#include <stdio.h>
int count_char(const char *str, char c) {
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            count++;
    return count;
}

void remove_quotes(char *str)
{
    int single_quotes = count_char(str, '\'');
    int double_quotes = count_char(str, '"');

    int remove_single = (single_quotes % 2 == 0);
    int remove_double = (double_quotes % 2 == 0);

    int i = 0, j = 0;
    int in_single = 0, in_double = 0;

    while (str[i]) {
        if (str[i] == '\'' && !in_double && remove_single) {
            in_single = !in_single;
            i++;
        }
        else if (str[i] == '"' && !in_single && remove_double) {
            in_double = !in_double;
            i++;
        }
        else {
            str[j++] = str[i++];
        }
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


void    quotes(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
	{
		remove_quotes(str[i]);
		i++;
	}
}

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
