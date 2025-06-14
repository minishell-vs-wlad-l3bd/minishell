#include "../main/minishell.h"

char *extract_name(char *str, t_garbege **head)
{
    int i;

    i = 0;
    if (!str || !*str)
        return NULL;
    if (str[i] == '?')
        return ft_strdup("?", head);
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    return ft_substr(str, 0, i, head);
}

char    *expand_value(char *str, t_mini *mini, t_garbege **head)
{
    char    *var_name;
    char    *value;
	int	    i;

    var_name = extract_name(str, head);
    value = NULL;
	i = 0;
    if (!var_name)
        return NULL;
    if (ft_strcmp(var_name, "?") == 0)
        value = ft_itoa(mini->exit, head);
    else
        value = get_env_value(mini, var_name);
    if (value)
        return ft_strdup(value, head);
    else
        return (NULL);
}

char *prepare_and_expand(char *result, char *var_start, t_mini *mini, char **new_result, t_garbege **head)
{
    char    *before;
    char    *var_name;
    char    *value;
    int     var_len;
    char    *after;
    char    *tmp;
	
	value = NULL;
	var_len = 1;
	tmp = NULL;
	var_name = extract_name(var_start + 1, head);
	before = ft_substr(result, 0, var_start - result, head);
    if (!before)
        return NULL;
    if (var_name)
    {
        value = expand_value(var_start + 1, mini, head);
        var_len += ft_strlen(var_name);
    }
    after = ft_strdup(var_start + var_len, head);
    if (!after || !value)
        return NULL;
    tmp = ft_strjoin(before, value, head);
    *new_result = ft_strjoin(tmp, after, head);
    return *new_result;
}

char *expand_string(char *str, t_mini *mini, t_garbege **head)
{
    char *result;
    char *var_start;
    char *new_result;

    if (!str)
		return NULL;
	result = ft_strdup(str, head);
    while ((var_start = ft_strchr(result, '$')))
    {
        if (!prepare_and_expand(result, var_start, mini, &new_result, head))
            return NULL;
        result = new_result;
    }
    return result;
}
