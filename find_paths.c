#include "minishell.h"

char *get_env_value(t_env *env, char *key)
{
    
    if (!env || !key)
        return NULL;
    while (env)
    {
        if (env->key && !ft_strcmp(env->key, key))
            return env->value;
        env = env->next;
    }
    return NULL;
}

char *find_cmd_path(char **paths, char *cmd)
{
    char *cmd_p;
    char *tmp;
    
    if (!cmd || !paths)
        return NULL;
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, F_OK | X_OK) == 0)
            return ft_strdup(cmd);
        return NULL;
    }
	int i = -1;
    while (paths[++i])
    {
        tmp = ft_strjoin(paths[i], "/");
        if (!tmp)
			return NULL;
        cmd_p = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!cmd_p)
			return NULL;
        if (access(cmd_p, F_OK | X_OK) == 0)
            return cmd_p;
        free(cmd_p);
    }
    return NULL;
}
