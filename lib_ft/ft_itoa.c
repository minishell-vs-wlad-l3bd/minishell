/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:26:01 by mohidbel          #+#    #+#             */
/*   Updated: 2024/11/15 11:46:58 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_int_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static	void	tap_number(int n, char *str, int len)
{
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		tap_number(147483648, str, len);
	}
	else if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	if (n == 0)
		str[len] = '0';
	else
	{
		while (n > 0)
		{
			str[len] = (n % 10) + 48;
			n /= 10;
			len--;
		}
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = get_int_len(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	tap_number(n, str, len - 1);
	return (str);
}
