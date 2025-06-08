#include "../main/minishell.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int word_len(const char *s, int use_quote)
{
    int i = 0;
    char quote = 0;

    if (!use_quote)
    {
        while (s[i] && !ft_isspace(s[i]))
            i++;
        return i;
    }
    while (s[i])
    {
        if (!quote && is_quote(s[i]))
            quote = s[i++];
        else if (quote && s[i] == quote)
        {
            quote = 0;
            i++;
        }
        else if (!quote && ft_isspace(s[i]))
            break;
        else
            i++;
    }
    return i;
}

static int	word_count(const char *s, int use_quote)
{
	int i = 0;
	int count = 0;
	int len;

	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			len = word_len(&s[i], use_quote);
			i += len;
			count++;
		}
	}
	return count;
}

static char *wordcopy(const char *s, int use_quote)
{
    int len = word_len(s, use_quote);
    char *word = malloc(len + 1);
    int i = 0, j = 0;
    char quote = 0;

    if (!word)
        return NULL;

    if (!use_quote)
    {
        while (i < len)
            word[j++] = s[i++];
    }
    else
    {
        while (i < len)
        {
            if (!quote && is_quote(s[i]))
                quote = s[i];
            else if (quote && s[i] == quote)
                quote = 0;
            word[j++] = s[i++];
        }
    }
    word[j] = '\0';
    return word;
}


char **split(const char *s, int use_quote)
{
	char **arr;
	int i = 0;
	int count;

	if (!s)
		return NULL;
	count = word_count(s, use_quote);
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return NULL;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
		{
			arr[i] = wordcopy(s, use_quote);
			if (!arr[i])
				return NULL;
			s += word_len(s, use_quote);
			i++;
		}
	}
	arr[i] = NULL;
	return arr;
}
