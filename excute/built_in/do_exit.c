/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:53 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/27 19:46:56 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

char *normalize_number(char *str)
{
	while (*str == '0' && *(str + 1) != '\0')
		str++;
	return str;
}

int is_too_big(char *str)
{
	int len;
	char *max = "9223372036854775807";
	char *min = "9223372036854775808";

	if (str[0] == '+' || str[0] == '-')
		str++;
	str = normalize_number(str);
	len = ft_strlen(str);

	if (len < 19)
		return (0);
	else if (len > 19)
		return (1);

	if (str[-1] == '-')
		return (ft_strcmp(str, min) > 0);
	else
		return (ft_strcmp(str, max) > 0);
}

void do_exit(char **args, t_mini *mini)
{
	long status = 0;
	int i = 0;
	int is_numeric = 1;

	if (args[1])
	{
		if (args[1][i] == '+' || args[1][i] == '-')
			i++;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				is_numeric = 0;
				break;
			}
			i++;
		}
		if (!is_numeric || is_too_big(args[1]))
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: exit: numeric argument required\n", STDERR_FILENO);
			exit(255);
		}
		status = ft_atoi(args[1]);
		if (args[2])
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			mini->exit = 1;
			return ;
		}
	}
	if (mini->in != STDIN_FILENO)
		close(mini->in);
	if (mini->out != STDOUT_FILENO)
		close(mini->out);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(status % 256);
}
