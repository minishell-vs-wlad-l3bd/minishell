/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:38:32 by mohidbel          #+#    #+#             */
/*   Updated: 2024/11/04 11:22:26 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	n;

	n = 0;
	while (s[n] != '\0')
		n++;
	if ((unsigned char)c == '\0')
		return ((char *)(s + n));
	while (n > 0)
	{
		n--;
		if ((unsigned char)s[n] == (unsigned char)c)
			return ((char *)(s + n));
	}
	return (0);
}
