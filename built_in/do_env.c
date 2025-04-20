#include "../minishell.h"

void	do_env(t_env *env)
{

	while (env)
	{
		if(!env->n)
		{
			printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
		else
			break;
	}
}
