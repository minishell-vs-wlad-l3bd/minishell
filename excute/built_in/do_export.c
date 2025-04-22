#include "../excute.h"

void ft_sort(t_mini *mini)
{
	t_env *current;
	t_env *next_node;
	char *tmp;

	if (!mini->export_env)
		return ;
	current = mini->export_env;
	while (current)
	{
		next_node = current->next;
		while (next_node)
		{
			if (strcmp(current->key, next_node->key) > 0)
			{
				tmp = current->key;
				current->key = next_node->key;
				next_node->key = tmp;
			}
			next_node = next_node->next;
		}
		current = current->next;
	}
}

void print_sort_env(t_mini *mini)
{
	t_env *node = mini->export_env;
	ft_sort(mini);
	while (node)
	{
		printf("export : ");
		printf("%s=", node->key);
		if (!node->value)
			printf("\"%s\"\n", node->value);
		else
			printf("\"\"\n"); 
		node = node->next;
	}
}

void env_add(t_mini *mini, char *s)
{
	char **tmp;
	t_env *node;

	node = mini->export_env;
	if(!ft_strchr(s, '='))
	{
		ft_env_lstadd_back(&node, ft_env_lstnew(ft_strdup(s), ft_strdup(""), 1));
	}
	else
	{
		tmp = ft_split(s, '=');
		if(tmp)
		{
			if(tmp[1])
				ft_env_lstadd_back(&node, ft_env_lstnew(ft_strdup(tmp[0]), ft_strdup(tmp[1]), 1));
			else
				ft_env_lstadd_back(&node, ft_env_lstnew(ft_strdup(tmp[0]), ft_strdup(""), 1));
		}
		
	}
}

void do_export(char **args, t_mini *mini)
{
	if (!args[1])
	{
		print_sort_env(mini);
	}
	else
		env_add(mini, args[1]);
}