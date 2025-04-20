#include "../minishell.h"

void	ft_env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if(lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*ft_env_lstnew(void *key, void *value, char *var, int n)
{
	t_env	*node1;

	if(!var)
		return NULL;
	node1 = ft_malloc(sizeof(t_env));
	if (node1 == NULL)
		return (NULL);
	node1->value = value;
	node1->key = key;
	node1->var = var;
	node1->n = n;
	node1->next = NULL;
	return (node1);
}
