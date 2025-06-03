/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:26:00 by aayad             #+#    #+#             */
/*   Updated: 2025/05/31 10:26:01 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	word_len(const char *s, char sep)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	while (s[i])
	{
		if (!quote && is_quote(s[i]))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else if (!quote && s[i] == sep)
			break ;
		i++;
	}
	return (i);
}

static int	word_count(const char *s, char sep)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if (s[i])
		{
			len = word_len(&s[i], sep);
			i += len;
			count++;
		}
	}
	return (count);
}

static char	*wordcopy(const char *s, char sep)
{
	int		len;
	char	*word ;
	int		i;
	int		j;
	char	quote;

	j = 0;
	quote = 0;
	len = word_len(s, sep);
	word = ft_malloc(len + 1);
	i = 0;
	j = 0;
	quote = 0;
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[j++] = s[i];
		i++;
	}
	word[j] = '\0';
	return (word);
}

char	**split(const char *s, char sep)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	arr = ft_malloc((word_count(s, sep) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == sep)
			s++;
		if (*s)
		{
			arr[i] = wordcopy(s, sep);
			if (!arr[i])
				return (NULL);
			s += word_len(s, sep);
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
