#include "../main/minishell.h"

static bool	in_quote(char c, char *quote)
{
	if (*quote == '\0' && (c == '"' || c == '\''))
		*quote = c;
	else if (*quote == c)
		*quote = '\0';
	return (*quote != '\0');
}

static int	word_len(const char *s, char sep)
{
	int		i;
	char	quote;

	quote = '\0';
	i = 0;
	while (s[i])
	{
		if (in_quote(s[i], &quote))
		{
			i++;
			continue;
		}
		if (!quote && s[i] == sep)
			break;
		i++;
	}
	return (i);
}

static int	count_words(const char *s, char sep)
{
	int		i;
	int		count;
	char	quote ;

	quote = '\0';
	i = 0;
	count = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
			count++;
		i = word_len(s, sep);
		s += i;
	}
	return (count);
}

static char	*copy_word(const char *s, int len)
{
	char	*word ;
	int		i;

	word = ft_malloc(len + 1);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_all(char **arr, int count)
{
	while (--count >= 0)
		free(arr[count]);
	free(arr);
}

char	**split_by_pipe(const char *s, t_mini *mini)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	if(count_words(s, '|') > 1)
		mini->pipe = 1;
	result = ft_malloc((count_words(s, '|') + 1) * sizeof(char *));
	while (*s)
	{
		while (*s == '|')
			s++;
		if (!*s)
			break;
		if ((result[i] = copy_word(s, word_len(s, '|'))) == 0)
			return (free_all(result, i), NULL);
		s += word_len(s, '|');
		i++;
	}
	result[i] = NULL;
	return (result);
}
