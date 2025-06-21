/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:04:34 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/16 17:03:35 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int n, size_t len, t_garbege **head)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (n >= s_len)
		return (ft_strdup("", head));
	if (len > s_len - n)
		len = s_len - n;
	substr = ft_malloc((len + 1) * sizeof(char), head);
	i = 0;
	while (i < len && s[n + i] != '\0')
	{
		substr[i] = s[n + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
