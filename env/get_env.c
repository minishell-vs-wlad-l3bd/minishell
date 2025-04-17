#include "../minishell.h"

void update_env(t_env **env, char *key, char *value)
{
    size_t k_len;
    size_t v_len;
    char *new;
    t_env *c;

    if (!env || !key || !value)
        return;
    k_len = ft_strlen(key);
    v_len = ft_strlen(value);
    new = ft_malloc(k_len + v_len + 2);
    if (!new)
    {
        perror("minishell: ft_malloc");
        return;
    }
    ft_memcpy(new, key, k_len);
    new[k_len] = '=';
    ft_memcpy(new + k_len + 1, value, v_len);
    new[k_len + v_len + 1] = '\0';
    c = *env;
    while (c)
    {
        if (c->value && !strncmp(c->value, key, k_len) && c->value[k_len] == '=')
        {
            c->value = new;
            return;
        }
        c = c->next;
    }
    c = ft_malloc(sizeof(t_env));
    if (!c)
        return;
    c->value = new;
    c->next = *env;
    *env = c;
}

t_env	*env_init(char **env)
{
	int		i;
	t_env	*head;

	head = NULL;
	i = 1;
    if(!env)
    {
        return (NULL);
    }
	while (env[i])
    {
		ft_env_lstadd_back(&head, ft_env_lstnew(ft_strdup(env[i])));
        i++;
    }
	return (head);
}