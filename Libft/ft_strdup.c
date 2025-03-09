/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:53:59 by mohidbel          #+#    #+#             */
/*   Updated: 2024/11/14 15:41:09 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	int		s1len;

	s1len = 0;
	while (s1[s1len] != '\0')
		s1len++;
	i = 0;
	s2 = malloc((s1len + 1) * sizeof(char));
	if (s2 == NULL)
		return (0);
	while (i < s1len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
