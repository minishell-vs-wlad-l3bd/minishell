/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:03:14 by mohidbel          #+#    #+#             */
/*   Updated: 2024/11/04 11:26:45 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_overlap(char *d, const char *s, size_t len)
{
	size_t	n;

	if (d > s)
	{
		n = len;
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	else if (d < s)
	{
		n = 0;
		while (n < len)
		{
			d[n] = s[n];
			n++;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*s;
	char		*d;

	d = (char *) dst;
	s = (const char *) src;
	if (!dst && !src && len > 0)
		return (NULL);
	check_overlap(d, s, len);
	return (dst);
}
