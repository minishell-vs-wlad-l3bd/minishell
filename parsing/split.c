/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:25:34 by aayad             #+#    #+#             */
/*   Updated: 2025/07/04 10:54:44 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

static int	word_len(const char *s)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
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

static int	word_count(const char *s)
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
			len = word_len(&s[i]);
			i += len;
			count++;
		}
	}
	return (count);
}

static char	*wordcopy(const char *s, t_garbege **head)
{
	int		len;
	char	*word;
	int		i;
	int		j;
	int		quote;

	len = word_len(s);
	word = ft_malloc(len + 1, head);
	if (!word)
		return (NULL);
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
	return (word);
}

char	**split(const char *s, t_garbege **head)
{
	char	**arr;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	i = 0;
	count = word_count(s);
	arr = ft_malloc((count + 1) * sizeof(char *), head);
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
		{
			arr[i] = wordcopy(s, head);
			if (!arr[i])
				return (NULL);
			s += word_len(s);
			i++;
		}
	}
	return (arr[i] = NULL, arr);
}
