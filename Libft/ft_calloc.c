/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:22:33 by mohidbel          #+#    #+#             */
/*   Updated: 2024/11/04 11:40:17 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	char	*ptr;
	size_t	i;

	total_size = count * size;
	if (count && total_size / count != size)
		return (NULL);
	ptr = malloc((total_size) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (total_size > i)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
