#include "../main/minishell.h"

char *extract_name(char *str)
{
    int i = 0;
    
    if (!str || !*str)
        return NULL;
    if (str[i] == '?')
        return ft_strdup("?");
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    return ft_substr(str, 0, i);
}

char *expand_value(char *str, t_mini *mini)
{
    char *var_name;
    char *value;

    var_name = extract_name(str);
    value = NULL;
    if (!var_name)
        return NULL;
    if (ft_strcmp(var_name, "?") == 0)
        value = ft_itoa(g_exit_status);
    else
        value = get_env_value(mini, var_name);
    if (value)
        return ft_strdup(value);
    else
        return (NULL);
}

char *prepare_and_expand(char *result, char *var_start, t_mini *mini, char **new_result)
{
    char *before = ft_substr(result, 0, var_start - result);
    char *var_name = extract_name(var_start + 1);
    char *value = NULL;
    int var_len = 1;
    char *after = NULL;
    char *tmp = NULL;

    if (!before)
        return NULL;
    if (var_name)
    {
        value = expand_value(var_start + 1, mini);
        var_len += ft_strlen(var_name);
    }
    after = ft_strdup(var_start + var_len);
    if (!after || !value)
        return NULL;
    tmp = ft_strjoin(before, value);
    *new_result = ft_strjoin(tmp, after);
    return *new_result;
}

char *expand_string(char *str, t_mini *mini)
{
    char *result;
    char *var_start;
    char *new_result;

    if (!str)
		return NULL;
	result = ft_strdup(str);
    while ((var_start = ft_strchr(result, '$')))
    {
        if (!prepare_and_expand(result, var_start, mini, &new_result))
            return NULL;
        free(result);
        result = new_result;
    }
    return result;
}
