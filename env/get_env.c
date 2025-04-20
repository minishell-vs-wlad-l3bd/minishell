#include "../minishell.h"

void update_env(t_env **env, char *key, char *value)
{
	size_t v_len;
	char *new;
	t_env *c;

	if (!env || !key || !value)
		return;
	v_len = ft_strlen(value);
	new = ft_malloc(v_len + 1);
	if (!new)
	{
		perror("minishell: ft_malloc");
		return;
	}
	ft_memcpy(new, value, v_len);
	new[v_len] = '\0';
	c = *env;
	while (c)
	{
		if (c->key && !ft_strcmp(c->key, key))
		{
			if (c->value)
                free(c->value);
			c->value = new;
			return;
		}
		c = c->next;
	}
	c = ft_malloc(sizeof(t_env));
	if (!c)
		return;
	c->key = key;
	c->value = new;
	c->next = *env;
	*env = c;
}

t_env	*env_init(char **env)
{
	int		i;
	t_env	*head;
	char **tmp;

	head = NULL;
	i = 0;
	if(!env)
		return (NULL);
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		t_env *new_node = ft_env_lstnew(tmp[0], tmp[1], env[i], 0);
		ft_env_lstadd_back(&head, new_node);
		free(tmp);
		i++;
	}
	return (head);
}