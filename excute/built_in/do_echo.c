/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:39 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/08 16:33:23 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

static int is_valid_n_flag(const char *str)
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

static char	*join_args(char **cmd, int i)
{
	char	*buff;
	char	*tmp;
	char	*joined;

	buff = ft_strdup("");
	while (cmd[i])
	{
		if (!cmd[i][0])
		{
			i++;
			continue;
		}
		if (cmd[i + 1])
			tmp = ft_strjoin(cmd[i], " ");
		else
			tmp = ft_strdup(cmd[i]);
		joined = ft_strjoin(buff, tmp);
		free(buff);
		free(tmp);
		buff = joined;
		i++;
	}
	return (buff);
}

void	do_echo(t_mini *mini)
{
	t_parsing	*parss;
	int			i;
	int			nl;
	char		*buff;

	parss = mini->parss;
	i = 1;
	i = 1;
	nl = 0;
	// quotes(parss->cmd);
	while (parss->cmd[i] && is_valid_n_flag(parss->cmd[i]))
	{
		nl = 1;
		i++;
	}
	buff = join_args(parss->cmd, i);
	if (nl)
		printf("%s", buff);
	else
		printf("%s\n", buff);
}
