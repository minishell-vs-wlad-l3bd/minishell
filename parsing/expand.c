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

    if (!result)
		return NULL;
	result = ft_strdup(str);
    while ((var_start = ft_strchr(result, '$')))
    {
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

void remove_token(char **arr, int idx)
{
    free(arr[idx]);
    while (arr[idx])
    {
        arr[idx] = arr[idx + 1];
        idx++;
    }
}

void replace_expand_to_value(t_mini *mini)
{
    t_parsing *parss ;
    char *expanded;
    char *original;
    int i;

	parss = mini->parss;
    while (parss)
    {
        i = 0;
        while (parss->cmd && parss->cmd[i])
        {
			original = parss->cmd[i];
			expanded = expand_string(original, mini);
			if (expanded)
            {
                if (expanded != original)
                {
                    free(parss->cmd[i]);
                    parss->cmd[i] = expanded;
                }
                i++;
            }
            else
                remove_token(parss->cmd, i);
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