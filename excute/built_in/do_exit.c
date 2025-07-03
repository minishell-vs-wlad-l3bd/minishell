/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:53 by mohidbel          #+#    #+#             */
/*   Updated: 2025/07/03 18:25:26 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

static char	*normalize_number(char *str)
{
	while (*str == '0' && *(str + 1) != '\0')
		str++;
	return (str);
}

static int	is_too_big(char *str)
{
	int		len;
	int		is_negative;
	char	*max;
	char	*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
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

static int	is_numeric_str(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
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

static void	exit_with_error(t_mini *mini, t_garbege **head)
{
	close(mini->in);
	close(mini->out);
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	ft_free_all(head);
	rl_clear_history();
	exit(255);
}

void	do_exit(char **args, t_mini *mini, t_garbege **head)
{
	long	status;

	status = 0;
	if (args[1])
	{
		if (!is_numeric_str(args[1]) || is_too_big(args[1]) || !args[1][0])
			exit_with_error(mini, head);
		if (args[2])
		{
			mini->exit = 1;
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return ;
		}
		status = ft_atoi(args[1]);
	}
	else if (!mini->pipe)
		(close(mini->in), close(mini->out), rl_clear_history(),
			ft_putstr_fd("exit\n", 2), ft_free_all(head), exit(mini->exit));
	close(mini->in);
	close(mini->out);
	if (mini->pipe)
		(ft_free_all(head), rl_clear_history(), exit(status % 256));
	(ft_putstr_fd("exit\n", 2), rl_clear_history(),
		ft_free_all(head), exit(status % 256));
}
