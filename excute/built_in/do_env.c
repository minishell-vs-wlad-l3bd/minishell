#include "../excute.h"

void	do_env(t_mini *mini)
{
	t_env *node;

	node = mini->env;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
}
