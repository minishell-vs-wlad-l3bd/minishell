/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:53 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/08 15:42:17 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

char *normalize_number(char *str)
{
	while (*str == '0' && *(str + 1) != '\0')
		str++;
	return str;
}

int	is_too_big(char *str)
{
	int		len;
	char	*max = "9223372036854775807";
	char	*min = "9223372036854775808";
	int		is_negative;

	is_negative = (*str == '-');
	if (*str == '+' || *str == '-')
		str++;
	str = normalize_number(str);
	len = ft_strlen(str);
	if (len < 19)
		return (0);
	if (len > 19)
		return (1);
	if (is_negative)
		return (ft_strcmp(str, min) > 0);
	return (ft_strcmp(str, max) > 0);
}

int	is_numeric_str(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	do_exit(char **args, t_mini *mini)
{
	long	status;

	status = 0;
	if (args[1])
	{
		if (!is_numeric_str(args[1]) || is_too_big(args[1]))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			ft_free_all();
			exit(255);
		}
		status = ft_atoi(args[1]);
		if (args[2])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_exit_status = 1;
			return ;
		}
	}
	if (mini->in != STDIN_FILENO)
		close(mini->in);
	if (mini->out != STDOUT_FILENO)
		close(mini->out);
	if (mini->pipe)
	{
		ft_free_all();
		exit(status % 256);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_free_all();
		exit(status % 256);
	}
}
