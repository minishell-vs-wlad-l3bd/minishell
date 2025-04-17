#include "../minishell.h"

void update_env(t_env **env, char *key, char *value)
{
    size_t k_len;
    size_t v_len;
    char *new;
    t_env *c;

    if (!env || !key || !value) // hadle dyal segfault
        return;

    k_len = ft_strlen(key);
    v_len = ft_strlen(value);
    new = malloc(k_len + v_len + 2); // +1 dyal "=", +1 dyal "\0"
    if (!new)
    {
        perror("minishell: malloc");
        return;
    }
    // hadi bach n3mr string dyal bl key ya3ni dik path li 9bl = ola home
    ft_memcpy(new, key, k_len);
    new[k_len] = '='; // hna kanzid =
    // hadi dyal dakchi li mora =
    memcpy(new + k_len + 1, value, v_len);
    new[k_len + v_len + 1] = '\0'; // hadi rah bayna
    c = *env;
    while (c)
    {
        if (c->value && !strncmp(c->value, key, k_len) && c->value[k_len] == '=')
        {
            c->value = new;
            return;
        }
        c = c->next;
    }

    // Add new variable if not found
    c = malloc(sizeof(t_env));
    if (!c)
    {
        perror("minishell: malloc");
        return;
    }
    c->value = new;
    c->next = *env;
    *env = c;
}

void do_cd(char **cmd, t_env **env)
{
    char cwd[PATH_MAX];
    char *target = NULL;
    char *error = NULL;
    int print_newdir = 0;

    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd");
        return;
    }
    if (!cmd[1])
    {
        target = get_env_value(*env, "HOME");
        if (!target)
            error = "HOME not set";
    }
    else if (strcmp(cmd[1], "-") == 0)
    {
        target = get_env_value(*env, "OLDPWD");
        if (!target)
            error = "OLDPWD not set";
        else
            print_newdir = 1;
    }
    else
        target = cmd[1]; 
    if (!error && target)
    {
        if (chdir(target) != 0)
            error = "fail chadir";
        else
        {
            update_env(env, "OLDPWD", cwd);
            update_env(env, "PWD", getcwd(cwd, sizeof(cwd)));
            if (print_newdir)
                if (getcwd(cwd, sizeof(cwd)))
                    printf("%s\n", cwd);
        }
    }
    if (error)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(error, 2);
    }
}
