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
            if (strcmp(current->value, next_node->value) > 0)
            {
                tmp = current->value;
                current->value = next_node->value;
                next_node->value = tmp;
            }
            next_node = next_node->next;
        }
        current = current->next;
    }
}

void print_sort_env(t_env **env)
{
    t_env *l = *env;
    ft_sort(env);
    while (l)
    {
        printf("export : ");
        printf("%s\n", l->value);
        l = l->next;
    }
}

// void env_add()
// {
// }

void do_export(char **args, t_env **env)
{
    if (!args[1])
    {
        print_sort_env(env);
    }
    // else
    // {
    //     env_add();
    // }
}