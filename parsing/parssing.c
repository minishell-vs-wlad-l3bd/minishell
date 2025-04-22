# include "../main/minishell.h"

void	remove_quotes(char *str)
{
	int	i;
	int	j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				str[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

void    quotes(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		remove_quotes(str[i]);
		i++;
	}
}
