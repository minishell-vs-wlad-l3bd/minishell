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
	if (!strcmp(cmd[0], "cd"))
		do_cd(cmd, mini);
	else if(!strcmp(cmd[0], "echo"))
		do_echo(cmd);
	else if (!strcmp(cmd[0], "exit"))
		do_exit(cmd, mini);
	else if(!strcmp(cmd[0], "pwd"))
		do_pwd(mini);
	else if(!strcmp(cmd[0], "export"))
		do_export(cmd, mini);
	else if(!strcmp(cmd[0], "unset"))
		do_unset(&cmd[1], mini);
	else if(!strcmp(cmd[0], "env"))
		do_env(mini);
}

void execute_cmd(char **paths, char **cmd, t_mini *mini)
{
	pid_t pid;
	char *cmd_path = find_cmd_path(paths, cmd[0]);
	if (!cmd_path)
    {
		printf("minishell: %s: command not found\n", cmd[0]);
        mini->exit = 127;
		return ;
    }
	pid = fork();
	if (pid == 0)
	{
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
		execve(cmd_path, cmd, mini->ev);
	}
	else
		waitpid(pid, NULL, 0);
}


int check_type(char *str, char **paths, t_mini *mini)
{
	t_tokens *tokens;

	tokens = mini->parss->token;
	while(tokens && (tokens->heredoc || tokens->append || tokens->intput || tokens->output))
	{
		if (tokens->heredoc)
		{
			heredoc(mini, str);
			return 1;
		}
		else if (tokens->append || tokens->intput || tokens->output)
		{
			if(handle_redirections(tokens))
				return 1;
			else
				return 0;
		}
		tokens = tokens->next;
	}
	return 1;
}


void ft_execute(t_mini *mini, char *str)
{
	pid_t pid;
    char **paths;

    paths = ft_split(get_env_value(mini, "PATH"), ':');
	update_env(&mini->env, "_", mini->parss->cmd[0]);
	update_env(&mini->export_env, "_", mini->parss->cmd[0]);
    if (mini->pipe)
	{
        execute_pipeline(str, paths, mini);
        return ;
	}
    if(!check_type(str, paths, mini))
		return ;
	if (!mini->parss->cmd[0])
		return ;
    if (is_builtin(mini->parss->cmd[0]))
        execute_builtin(mini->parss->cmd, mini);
    else
		execute_cmd(paths, mini->parss->cmd, mini);
}
