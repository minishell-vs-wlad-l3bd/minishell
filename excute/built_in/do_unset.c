#include "../excute.h"

void remove_env_var(char *var, t_mini *mini)
{
    t_env *temp = mini->env;
    t_env *prev = NULL;
    size_t len;
    
    len  = ft_strlen(var);
    while (temp)
    {
        if (ft_strcmp(temp->key, var) == 0)
        {
            if (prev)
                prev->next = temp->next;
            else
                mini->env = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

int is_invalid_identifier(char *str)
{
    int i = 0;

    if (!str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
    {
        ft_putendl_fd("unset: invalid identifier", STDERR_FILENO);
        return 1;
    }
    while (str[++i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
        {
            ft_putendl_fd("unset: invalid identifier", STDERR_FILENO);
            return 1;
        }
    }
    return 0;
}

void do_unset(char **args, t_mini *mini)
{
    int i = 0;

    while (args[i])
    {
        if (!is_invalid_identifier(args[i]))
            remove_env_var(args[i], mini);
        i++;
    }
}
