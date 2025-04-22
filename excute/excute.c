#include "excute.h"

int is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

void execute_builtin(char **cmd, t_mini *mini)
{
	quotes(&cmd[1]);
	if (!strcmp(cmd[0], "cd"))
		do_cd(cmd, mini);
	else if(!strcmp(cmd[0], "echo"))
		do_echo(&cmd[1]);
	else if (!strcmp(cmd[0], "exit"))
		do_exit(cmd, mini);
	else if(!strcmp(cmd[0], "pwd"))
		do_pwd();
	else if(!strcmp(cmd[0], "export"))
		do_export(cmd, mini);
	else if(!strcmp(cmd[0], "unset"))
		do_unset(&cmd[1], mini);
	else if(!strcmp(cmd[0], "env"))
		do_env(mini);
}

char **split_with_pipes(char *str)
{
	int i = 0;
	char **cmds = ft_split(str, '|');
	while (cmds[i])
	{
        cmds[i] = ft_strtrim(cmds[i], " ");
		i++;
	}
	return cmds;
}

pid_t execute(char **paths, char **cmd, t_mini *mini)
{
	pid_t pid;
	char *cmd_path = find_cmd_path(paths, cmd[0]);
	if (!cmd_path)
    {
		printf("minishell: %s: command not found\n", cmd[0]);
        mini->exit = 127;
        return -1;
    }
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, cmd, NULL);
		perror("execve failed");
		mini->exit = 127;
		exit(127);
	}
	return pid;
}

int check_type(char *str, char **paths, t_mini *mini)
{
    char **cmd = ft_split(str, ' ');
    char **cmds = split_with_pipes(str);

    if(ft_strchr(str, '|'))
        pipe_handle(cmds, paths, mini);
    else
        handle_redirections(cmd);
}

void ft_execute(t_mini *mini, char *str)
{
	pid_t pid;
    char **paths;
    char **cmd;

    paths = ft_split(get_env_value(mini, "PATH"), ':');
    cmd = ft_split(str, ' ');
    if (check_type(str, paths, mini))
        return ;
    else if (is_builtin(cmd[0]))
        execute_builtin(cmd, mini);
    else
	{
        pid = execute(paths, cmd, mini);
		if(pid > 0)
			waitpid(pid, NULL, 0);
	}
}
