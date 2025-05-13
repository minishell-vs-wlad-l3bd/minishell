#include "../excute.h"



int	is_numeric(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	do_exit(char **args, t_mini *mini)
{
	long	exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);

	if (args && args[0])
	{
		if (!is_numeric(args[1]) && args[1])
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit(255);
		}
		else if (args[1])	
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return; 
		}
		exit_code = ft_atoi(args[0]);
	}
	else
		exit_code = 0;
	exit((unsigned char)exit_code);
}
