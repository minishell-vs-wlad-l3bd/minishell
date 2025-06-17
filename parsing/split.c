/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:25:34 by aayad             #+#    #+#             */
/*   Updated: 2025/06/16 14:29:28 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

static int	word_len(const char *s, int use_quote)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	if (!use_quote)
	{
		while (s[i] && !ft_isspace(s[i]))
			i++;
		return (i);
	}
	while (s[i])
	{
		if (!quote && is_quote(s[i]))
			quote = s[i++];
		else if (quote && s[i] == quote)
			(1) && (quote = 0, i++);
		else if (!quote && ft_isspace(s[i]))
			break ;
		else
			i++;
	}
	return (i);
}

static int	word_count(const char *s, int use_quote)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
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
	return (count);
}

static void	copy_with_quotes(const char *s, char *word, int len)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (i < len)
	{
		if (!quote && is_quote(s[i]))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		word[j++] = s[i++];
	}
	word[j] = '\0';
}

static char	*wordcopy(const char *s, int use_quote, t_garbege **head)
{
	int		len;
	char	*word;
	int		i;
	int		j;

	len = word_len(s, use_quote);
	word = ft_malloc(len + 1, head);
	if (!word)
		return (NULL);
	if (!use_quote)
	{
		i = 0;
		j = 0;
		while (i < len)
			word[j++] = s[i++];
		word[j] = '\0';
	}
	else
		copy_with_quotes(s, word, len);
	return (word);
}

char	**split(const char *s, int use_quote, t_garbege **head)
{
	char	**arr;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	i = 0;
	count = word_count(s, use_quote);
	arr = ft_malloc((count + 1) * sizeof(char *), head);
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
		{
			arr[i] = wordcopy(s, use_quote, head);
			if (!arr[i])
				return (NULL);
			s += word_len(s, use_quote);
			i++;
		}
	}
	return (arr[i] = NULL, arr);
}
