#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
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
    while(1)
    {
        paths = ft_split(find_path(env), ':');
        char *str = readline("minishell ▶ ");
        cmd = ft_split(str, ' ');
        char *path_v = find_cmd_path(paths, cmd[0]);
        pid_t n = excuve_fonc(path_v, cmd);
        add_history(str);
        waitpid(n, NULL, 0);
    }
}