/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:53:59 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/18 18:55:27 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strdup(const char *s1)
{
    char *s2;
    int i;
    int s1len;

    i = 0;
    s1len = 0;
    if (!s1)
        return (NULL);
    while (s1[s1len] != '\0')
        s1len++;
    s2 = ft_malloc((s1len + 1) * sizeof(char));
    if (!s2)
        return (NULL);
    while (i < s1len)
    {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';
    return (s2);
}
