#include "excute.h"

char **env_list_to_array(t_env *env)
{
    int count = 0;
    char *key_equal;
    t_env *tmp = env;

    while (tmp) {
        count++;
        tmp = tmp->next;
    }
    char **arr = (char **)ft_malloc(sizeof(char *) * (count + 1));
    tmp = env;
    int i = 0;
    while (tmp)
    {
        key_equal = ft_strjoin(tmp->key, "=");
        arr[i] = ft_strjoin(key_equal, tmp->value);
        free(key_equal);
        tmp = tmp->next;
        i++;
    }
    arr[i] = NULL;
    return arr;
}

void    increment_shlvl(t_mini *mini)
{
    int shlvl;
    char *shlvl_value;

    shlvl_value = get_env_value(mini, "SHLVL");
    shlvl = ft_atoi(shlvl_value) + 1;
    update_env(&mini->env, "SHLVL", ft_itoa(shlvl));
    update_env(&mini->export_env, "SHLVL", ft_itoa(shlvl));
    mini->ev = env_list_to_array(mini->env);
}