/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:04:16 by mohidbel          #+#    #+#             */
/*   Updated: 2024/11/15 17:07:38 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*alls;
	int		maxlen;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	j = 0;
	i = 0;
	maxlen = ft_strlen(s1) + ft_strlen(s2);
	alls = malloc((maxlen + 1) * (sizeof(char)));
	if (alls == NULL)
		return (NULL);
	while (s1[i])
		alls[j++] = s1[i++];
	i = 0;
	while (s2[i])
		alls[j++] = s2[i++];
	alls[j] = '\0';
	return (alls);
}
