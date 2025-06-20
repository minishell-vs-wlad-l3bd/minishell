/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:52:49 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/16 17:03:14 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*wordcopy(char const *str, char c, t_garbege **head)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = ft_malloc((i +1) * sizeof(char), head);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c, t_garbege **head)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	arr = (char **)ft_malloc((wordcount(s, c) + 1) * sizeof(char *), head);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			arr[i] = wordcopy(s, c, head);
			if (!arr[i])
				return (NULL);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
