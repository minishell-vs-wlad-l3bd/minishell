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
    char cwd[PATH_MAX]; // hadi kayna limits.h kay3tina path max
    char *target = NULL;
    char *error = NULL;
    int print_newdir = 0;

    if (!getcwd(cwd, sizeof(cwd))) // hna kankhd path dyal folder li 9bl 
    {
        perror("minishell: cd");
        return;
    }
    if (!cmd[1]) // hna 3la 7sab ila drti cd bo7dha
    {
        target = get_env_value(*env, "HOME"); // hna kanstory dakchi ligdam home= fe target
        // kantchiki yakma variabl dyal home f env wach khawi
        if (!target)
            error = "HOME not set";
    }
    else if (strcmp(cmd[1], "-") == 0) // hna 3la 7sab cd - ila drti cd - kayrj3k lfolder li 9bl okyaktbo f stdrout 
    {
        target = get_env_value(*env, "OLDPWD");// kanstorih fe target
        if (!target)
            error = "OLDPWD not set";
        else
            print_newdir = 1; // hada bach ntchiki wach dkhl hna bach nktb 
    }
    else // hna dyal cd arg (libft or samthing .)
        target = cmd[1]; // fe target tani

    if (!error && target)
    {
        if (chdir(target) != 0) // hna fin kanbdl lfolder b chdir
            error = "fail chadir";
        else
        {
            update_env(env, "OLDPWD", cwd);
            if (print_newdir) // kaydkhl fi 7alat cd -
                if (getcwd(cwd, sizeof(cwd)))
                    printf("%s\n", cwd);
        }
    }
    if (error) // hadi ghir bach nktb error
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(error, 2);
    }
}
