/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:20:59 by aayad             #+#    #+#             */
/*   Updated: 2025/07/03 20:15:04 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			continue ;
		}
		if (!quote && s[i] == sep)
			break ;
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

static char	*copy_word(const char *s, int len, t_garbege **head)
{
	char	*word ;
	int		i;

	word = ft_malloc(len + 1, head);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**split_by_pipe(const char *s, t_mini *mini, t_garbege **head)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	if (count_words(s, '|') > 1)
		mini->pipe = 1;
	result = ft_malloc((count_words(s, '|') + 1) * sizeof(char *), head);
	while (*s)
	{
		while (*s == '|')
			s++;
		if (!*s)
			break ;
		result[i] = copy_word(s, word_len(s, '|'), head);
		if (result[i] == 0)
			return (NULL);
		s += word_len(s, '|');
		i++;
	}
	result[i] = NULL;
	return (result);
}
