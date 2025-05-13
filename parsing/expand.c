# include "../main/minishell.h"
#include <dirent.h>

char *expand_value(char *str, t_mini *mini)
{
    int i = 0;
    char *tmp;
    while (str[i])
    {
        if(str[i] == '$')
        {
            i++;
            tmp = get_env_value(mini, str + i);
            return tmp;
        }
        i++;
    }
    return NULL;
}


int check_valid_file(char *file, t_mini *mini)
{
    char *file_tmp;
    char *split;
    if (ft_strchr(file, '$'))
    {
        file_tmp = expand_value(file, mini);
        if(!file_tmp)
            return 0;
        split = ft_split(file_tmp, ' ');
        if(!split || split[1])
            return 0;
    }
    else
    {
        if(open(file, O_WRONLY, 0644) == -1)
            return 0;
    }
    return 1;
}
