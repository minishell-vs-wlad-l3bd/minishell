/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:39 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/01 10:10:53 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"


#include "../../main/minishell.h"


int is_valid_n_flag(const char *str)
{
	int i;

	i = 1;
	if (str[0] != '-')
		return 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}

void do_echo(t_mini *mini)
{
	t_parsing *parss;
	char *buff;
	char *tmp;
	int i;
	int nl;

	parss = mini->parss;
	i = 1;
	nl = 0;

	while (parss->cmd[i] && is_valid_n_flag(parss->cmd[i]))
	{
		nl = 1;
		i++;
	}
	buff = ft_strdup("");
	while (parss->cmd[i])
	{
		if (!parss->cmd[i] || !parss->cmd[i][0])
		{
			i++;
			continue;
		}
		if (parss->cmd[i + 1])
			tmp = ft_strjoin(parss->cmd[i], " ");
		else
			tmp = ft_strdup(parss->cmd[i]);
		buff = ft_strjoin(buff, tmp);
		i++;
	}
	if (nl == 1)
		printf("%s", buff);
	else
		printf("%s\n", buff);
}
