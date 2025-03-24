#include "../minishell.h"

t_env	*env_init(char **env)
{
	int		i;
	t_env	*head;

    if (!env)
        return NULL;
	head = NULL;
	i = -1;
	while (env[++i])
		ft_env_lstadd_back(&head, ft_env_lstnew(ft_strdup(env[i]))); // fhmha bohdk mafiyach 3yit
	return (head);
}