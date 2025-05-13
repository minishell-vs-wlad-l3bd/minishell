#include "../main/minishell.h"

void update_env(t_env **env, char *key, char *value)
{
	size_t v_len;
	char *new;
	t_env *c;

	if (!env || !key || !value)
		return ;
	v_len = ft_strlen(value);
	new = ft_malloc(v_len + 1);
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
	c->key = key;
	c->value = new;
	c->next = *env;
	*env = c;
}

void	env_pre_add(t_env **head, int flg)
{
	if (!flg)
	{
		ft_env_lstadd_back(head,
			ft_env_lstnew("PWD", getcwd(NULL, MAX_PATH)));
		ft_env_lstadd_back(head,
			ft_env_lstnew("SHLVL", ft_strdup("1")));
		ft_env_lstadd_back(head,
			ft_env_lstnew("_", "/usr/bin/env"));
	// 	ft_env_lstadd_back(head,
	// 		ft_env_lstnew("PATH",
	// 			"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	}
	else
	{
		ft_env_lstadd_back(head,
			ft_env_lstnew("OLDPWD", NULL));
		ft_env_lstadd_back(head,
			ft_env_lstnew("PWD", getcwd(NULL, MAX_PATH)));
		// ft_env_lstadd_back(head,
		// 	ft_env_lstnew("PATH",
		// 		"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
		ft_env_lstadd_back(head, ft_env_lstnew("SHLVL", ft_strdup("1")));
	}
}

int	double_arr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// char	*ft_env_eqls(char **res)
// {
// 	int		i;
// 	char	*out;
// 	char	*tmp;

// 	if (!res || !(*res))
// 		return (0);
// 	i = -1;
// 	out = NULL;
// 	while (res[++i])
// 	{
// 		tmp = res[i];
// 		if (out == NULL)
// 		{
// 			out = ft_strjoin(res[i], res[i + 1]);
// 			i++;
// 		}
// 		else
// 			out = ft_strjoin(out, res[i]);
// 	}
// 	return (out);
// }

t_env	*env_init(char **env, int flag)
{
	t_env	*head;
	t_env *new_node;
	int		i;
	char **tmp;

	head = NULL;
	i = 0;
	if(!env || !*env)
	{
		env_pre_add(&head, flag);
		return (head);
	}
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		if (double_arr_len(tmp) == 2)
			ft_env_lstadd_back(&head, ft_env_lstnew(tmp[0], tmp[1]));
		else if (double_arr_len(tmp) == 1)
			ft_env_lstadd_back(&head, ft_env_lstnew(tmp[0], ""));
		// else if (double_arr_len(tmp) > 2)
		// 	ft_env_lstadd_back(&head, ft_env_lstnew(tmp[0], ft_env_eqls(tmp), 1));
		i++;
	}
	return (head);
}
