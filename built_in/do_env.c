#include "../minishell.h"

void	do_env(t_env *env)
{
	while (env)
	{
		write(1, env->value, ft_strlen(env->value));
		write(1, "\n", 1);
		env = env->next;
	}
}
