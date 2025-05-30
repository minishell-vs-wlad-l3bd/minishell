#include "../main/minishell.h"

char *get_env_value(t_mini *mini, char *key)
{
    t_env *node;

    node = mini->env;
    if (!node || !key)
        return NULL;
    while (node)
    {
        if (node->key && !ft_strcmp(node->key, key))
            return node->value;
        node = node->next;
    }
    return NULL;
}

char *find_cmd_path(char **paths, char *cmd, t_mini *mini)
{
    char *cmd_p;
    char *tmp;
    
    if (!cmd)
        return (NULL);
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, F_OK) == -1)
            return (printf("minishell: %s: No such file or directory\n", cmd), mini->exit = 126, NULL);
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);
        return (printf("minishell: %s: Permission denied\n", cmd), mini->exit = 1, NULL);
    }
    if (!paths)
        return (printf("minishell: %s: command not found\n", cmd), mini->exit = 127, NULL);
    int i = -1;
    while (paths[++i])
    {
        tmp = ft_strjoin(paths[i], "/");
        if (!tmp)
            return (NULL);
        cmd_p = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!cmd_p)
            return (NULL);
        if (access(cmd_p, F_OK | X_OK) == 0)
            return (cmd_p);
        free(cmd_p);
    }
    return (printf("minishell: %s: command not found\n", cmd) ,mini->exit = 127, NULL);
}
