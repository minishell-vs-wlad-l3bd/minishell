#include "../minishell.h"

void ft_sort(t_env **env)
{
	t_env *current;
	t_env *next_node;
	char *tmp;

	if (!env || !*env)
		return;
	current = *env;
	while (current)
	{
		next_node = current->next;
		while (next_node)
		{
			if (strcmp(current->var, next_node->var) > 0)
			{
				tmp = current->var;
				current->var = next_node->var;
				next_node->var = tmp;
			}
			next_node = next_node->next;
		}
		current = current->next;
	}
}

void print_sort_env(t_env **env)
{
	char **str;
	t_env *l = *env;
	ft_sort(env);
	while (l)
	{
		str = ft_split(l->var, '=');
		printf("export : ");
		printf("%s=", str[0]);
		if (str[1])
			printf("\"%s\"\n", str[1]);
		else
			printf("\"\"\n"); 
		l = l->next;
	}
}

void env_add(t_env **env, char *s)
{
	char **tmp;
	// puts("a");
	if(!ft_strchr(s, '='))
	{
		ft_env_lstadd_back(env, ft_env_lstnew(ft_strdup(s), ft_strdup(""), ft_strdup(s), 1));
	}
	else
	{
		tmp = ft_split(s, '=');
		if(tmp)
		{
			if(tmp[1])
				ft_env_lstadd_back(env, ft_env_lstnew(ft_strdup(tmp[0]), ft_strdup(tmp[1]), ft_strdup(s), 1));
			else
				ft_env_lstadd_back(env, ft_env_lstnew(ft_strdup(tmp[0]), ft_strdup(""), ft_strdup(s), 1));
		}
		
	}
}

void do_export(char **args, t_env **env) // if var already have it just change value
{
	if (!args[1])
	{
		if(!ft_strchr(args[0], '='))
			print_sort_env(env);
		else
			env_add(env, args[1]);
	}
	else
		env_add(env, args[1]);
}