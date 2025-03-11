#include "minishell.h"

void handler(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env"))
		return (1);
	return (0);
}

// pid_t excuve_builtin(char *str)
// {
//     pid_t n = fork();
//     if(n == 0)
//     {
//         if(!strcmp(str, "cd"))
//             do_cd();
//         else if(!strcmp(str, "echo"))
//             do_echo();
//         else if(!strcmp(str, "pwd"))
//             do_pwd();
//         else if(!strcmp(str, "export"))
//             do_export();
//         else if(!strcmp(str, "unset"))
//             do_unset();
//         else if(!strcmp(str, "env"))
//             do_env();
//     }
//     return n;
// }


void ft_free(char **arr)
{
    int i = 0;
    while(arr[i])
        free(arr[i++]);
    free(arr);
}
pid_t excuve_fonc(char *path, char **alll)
{
    pid_t i = fork();
    if(i == 0)
        if(execve(path, alll, NULL) == -1)
            exit(1);
    return (i);
}

int main(int ac, char **av, char **env)
{
    char **paths;
    char **cmd;
	 char *path_v;
    ac = 1;
    av = NULL;
    while(1)
    {
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
        paths = ft_split(find_path(env), ':');
        char *str = readline("\033[34mminishell\033[0m \033[31m▶ \033[0m");
		if(!ft_strcmp(str, "exit") || str == NULL)
			exit(1);
		if (!str[0])
			continue;
        cmd = ft_split(str, ' ');
        path_v = find_cmd_path(paths, cmd[0]);
		if (!path_v)
			return (1);
        pid_t n = excuve_fonc(path_v, cmd);
        if (str == NULL)
        {
            printf("exit\n");
            break;
        }
        if(!strcmp(str, "exit"))
        {
            printf("exit\n");
            break;
        }
        if(!str[0])
            continue ;
        cmd = ft_split(str, ' ');
        // if(is_builtin(cmd[0]))
        //     excuve_builtin();
        // else
        // {
            char *path_v = find_cmd_path(paths, cmd[0]);
            if (path_v)
            {
                pid_t n = excuve_fonc(path_v, cmd);
                waitpid(n, NULL, 0);
                free(path_v);
            }
            else
                ft_putstr_fd("command not found\n", 2);
        // }
        add_history(str);
        free(str);
        ft_free(cmd);
        ft_free(paths);
    } 
    rl_clear_history();
}

