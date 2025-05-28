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
    if (i == 0)
        return ft_strdup("");
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
    if (ft_strlen(var_name) == 0)
        return ft_strdup("");
    if (ft_strcmp(var_name, "?") == 0)
        value = ft_itoa(mini->exit);
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
    if (value)
        tmp = ft_strjoin(before, value);
    else
        tmp = ft_strjoin(before, "");
    *new_result = ft_strjoin(tmp, after);
    return *new_result;
}

char *expand_string(char *str, t_mini *mini)
{
    char *result = ft_strdup(str);
    char *var_start;
    char *new_result;

    if (!result)
        return NULL;

    while ((var_start = ft_strchr(result, '$')))
    {
        if (var_start > result && *(var_start - 1) == '\\')
        {
            ft_memmove(var_start - 1, var_start, ft_strlen(var_start));
            continue;
        }
        if (!prepare_and_expand(result, var_start, mini, &new_result))
        {
            free(result);
            return NULL;
        }
        free(result);
        result = new_result;
    }

    return result;
}

void replace_expand_to_value(t_mini *mini)
{
    t_parsing *parss = mini->parss;
    char *expanded;
    char *original;
    int i;

    while (parss)
    {
        i = 0;
        while (parss->cmd && parss->cmd[i])
        {
            original = parss->cmd[i];
            expanded = expand_string(original, mini);
            if (expanded && expanded != original)
                parss->cmd[i] = expanded;
            else
                parss->cmd[i] = "";
            i++;
        }
        parss = parss->next;
    }
}

// int check_valid_file(char *file, t_mini *mini)
// {
//     char *file_tmp;
//     char **split;

//     if (ft_strchr(file, '$'))
//     {
//         file_tmp = expand_string(file, mini);
//         if (!file_tmp)
//             return 0;
//         split = ft_split(file_tmp, ' ');
//         if (!split || split[1])
//             return 0;
//     }
//     return 1;
// }