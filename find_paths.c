#include "minishell.h"

char *get_env_value(t_env *env, char *key)
{
    size_t key_len;
    
    if (!env || !key)
        return NULL;
    
    key_len = ft_strlen(key);
    while (env)
    {
        if (env->value && strncmp(env->value, key, key_len) == 0 && env->value[key_len] == '=')
            return env->value + key_len + 1;
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
	int i = -1
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
