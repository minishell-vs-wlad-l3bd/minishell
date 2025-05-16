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
			if (ft_strcmp(current->key, next_node->key) > 0)
			{
				tmp = current->key;
				current->key = next_node->key;
				next_node->key = tmp;
				tmp = current->value;
				current->value = next_node->value;
				next_node->value = tmp;
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
		printf("declare -x ");
		printf("%s", node->key);
		if (node->value)
			printf("=\'%s\'\n", node->value);
		else
			printf("\n"); 
		node = node->next;
	}
}

int check(t_env **env, char *key)
{
	t_env *node = *env;
	while(node)
	{
		if (!ft_strcmp(node->key, key))
			return 1;
		node = node->next;
	}
	return 0;
 }

void env_add(t_mini *mini, char *s)
{
	char **tmp;

	if(!ft_strchr(s, '='))
	{
		if (check(&mini->export_env, s) || check(&mini->env, s))
			return ;
		ft_env_lstadd_back(&mini->export_env, ft_env_lstnew(s, NULL));
	}
	else
	{
		tmp = ft_split(s, '=');

		if(tmp)
		{
			update_env(&mini->env, tmp[0], tmp[1]);
			update_env(&mini->export_env, tmp[0], tmp[1]);
		}
	}
}

void do_export(char **args, t_mini *mini)
{
	int i = 0;
	if (!args[1])
		print_sort_env(mini);
	else
	{
		while(args[++i])
			env_add(mini, args[i]);
	}
}