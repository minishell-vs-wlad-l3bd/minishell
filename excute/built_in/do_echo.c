/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:39 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/30 15:55:53 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

static int	is_valid_n_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static char	*join_args(char **cmd, int i, t_garbege **head)
{
	char	*buff;
	char	*tmp;
	char	*joined;

	buff = ft_strdup("", head);
	while (cmd[i])
	{
		if (!cmd[i][0])
		{
			i++;
			continue ;
		}
		if (cmd[i + 1])
			tmp = ft_strjoin(cmd[i], " ", head);
		else
			tmp = ft_strdup(cmd[i], head);
		joined = ft_strjoin(buff, tmp, head);
		buff = joined;
		i++;
	}
	return (buff);
}

void	do_echo(char **cmd, t_mini *mini, t_garbege **head)
{
	int			i;
	int			nl;
	char		*buff;

	i = 1;
	nl = 0;
	while (cmd[i] && is_valid_n_flag(cmd[i]))
	{
		nl = 1;
		i++;
	}
	buff = join_args(cmd, i, head);
	if (nl)
		ft_putstr_fd(buff, 1);
	else
		ft_putendl_fd(buff, 1);
	mini->exit = 0;
}
