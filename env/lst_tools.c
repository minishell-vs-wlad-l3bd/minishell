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

t_env	*ft_env_lstnew(void *content)
{
	t_env	*node1;

	node1 = ft_malloc(sizeof(t_env));
	if (node1 == NULL)
		return (NULL);
	node1->value = content;
	node1->next = NULL;
	return (node1);
}
