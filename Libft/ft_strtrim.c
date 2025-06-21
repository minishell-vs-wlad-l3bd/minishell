/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:15:31 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/16 17:03:28 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set, t_garbege **head)
{
	const char	*start;
	const char	*end;
	size_t		len;
	char		*t;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1, head));
	start = s1;
	end = s1 + ft_strlen(s1);
	while (*start && is_in_set(*start, set))
		start++;
	while (end > start && is_in_set(*(end - 1), set))
		end--;
	len = end - start;
	t = ft_malloc((len + 1) * sizeof(char), head);
	ft_strlcpy(t, start, len + 1);
	return (t);
}
