/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:27 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/23 14:12:28 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"


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

 void handle_append(t_mini *mini, char *str)
{
    char **parts;
    char *existing_value;
    char *new_value;
    char *key;
    char *value_part;

    parts = ft_split(str, '+');
    if (!parts || !parts[0] || !parts[1])
        return;
    
    key = parts[0];
    value_part = parts[1];
    
    if (value_part[0] != '=')
        return;
    existing_value = get_env_value(mini, key);
    value_part++;
    
    if (existing_value)
    {
        new_value = ft_strjoin(existing_value, value_part);
        update_env(&mini->env, key, new_value);
        update_env(&mini->export_env, key, new_value);
    }
    else
    {
        update_env(&mini->env, key, value_part);
        update_env(&mini->export_env, key, value_part);
    }
}

int is_valid_env_name(const char *name)
{
    const char *p = name;

    if (!name || !*name)
        return 0;
    if (!ft_isalpha(*p) && *p != '_')
        return 0;
    while (*++p)
    {
        if (!ft_isalnum(*p) && *p != '_')
        {
            if (*p == '=')
                break;
            if (*p == '+' && *(p+1) == '=')
                break;
            return 0;
        }
    }
    
    return 1;
}

void env_add(t_mini *mini, char *s)
{
    char **tmp;
    char *equal_sign;
    char *key;
    char *value;
	int key_len;

    if (!is_valid_env_name(s))
    {
        printf("export: `%s`: not a valid identifier\n", s);
        mini->exit = 1;
        return;
    }
    if (ft_strnstr(s, "+=",ft_strlen(s)))
    {
        handle_append(mini, s);
        return;
    }
    if(!ft_strchr(s, '='))
    {
        if (check(&mini->export_env, s) || check(&mini->env, s))
            return;
        ft_env_lstadd_back(&mini->export_env, ft_env_lstnew(s, NULL));
        return;
    }
    equal_sign = ft_strchr(s, '=');
    if (equal_sign)
    {
		key_len = equal_sign - s;
        key = ft_malloc(key_len + 1);
        ft_strlcpy(key, s, key_len + 1); 
        value = ft_strdup(equal_sign + 1);
        if (!is_valid_env_name(key))
        {
            printf("export: `%s`: not a valid identifier\n", s);
            mini->exit = 1;
            return;
        }
        update_env(&mini->env, key, value);
        update_env(&mini->export_env, key, value);
    }
}

void do_export(char **args, t_mini *mini)
{
	int i = 0;
	quotes(args);
	if (!args[1])
		print_sort_env(mini);
	else
	{
		while(args[++i])
			env_add(mini, args[i]);
	}
}