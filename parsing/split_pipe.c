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

	word = malloc(len + 1);
	i = 0;
	if (!word)
		return (NULL);
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

char	**split_by_pipe(const char *s)
{
	char	**result;
	int		i;
	int		len;
	int		words;

	if (!s)
		return (NULL);
	i = 0;
	words = count_words(s, '|');
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s == '|')
			s++;
		if (!*s)
			break;
		len = word_len(s, '|');
		result[i] = copy_word(s, len);
		if (!result[i])
		{
			free_all(result, i);
			return (NULL);
		}
		s += len;
		i++;
	}
	result[i] = NULL;
	return (result);
}
