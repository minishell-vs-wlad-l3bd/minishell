/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:44 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/08 15:43:53 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit") || !ft_strcmp(str, "ENV"))
		return (1);
	return (0);
}

void execute_builtin(char **cmd, t_mini *mini)
{
	if (!ft_strcmp(cmd[0], "cd"))
		do_cd(cmd, mini);
	else if(!ft_strcmp(cmd[0], "echo"))
		do_echo(mini);
	else if (!ft_strcmp(cmd[0], "exit"))
		do_exit(cmd, mini);
	else if(!ft_strcmp(cmd[0], "pwd"))
		do_pwd(mini);
	else if(!ft_strcmp(cmd[0], "export"))
		do_export(cmd, mini);
	else if(!ft_strcmp(cmd[0], "unset"))
		do_unset(&cmd[1], mini);
	else if(!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "ENV"))
		do_env(mini);
}

void execute_cmd(char **cmd, t_mini *mini)
{
	int status;
	pid_t pid;
	DIR *dir;
	char *cmd_path;

	cmd_path = find_cmd_path(mini->paths, *cmd);
	if (!cmd_path)
		return ;
	mini->ev=env_list_to_array(mini->env);
	if ((dir = opendir(*cmd)) != NULL)
	{
		closedir(dir);
		printf("minishell: %s: is a directory\n", *cmd);
		g_exit_status = 126;
		return ;
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		execve(cmd_path, cmd, mini->ev);
		exit(errno);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		setup_parent_signals();
	}
}

int check_type(t_mini *mini, int falg)
{
	t_tokens *tokens;
	char *last_heredoc_file;

	tokens = mini->parss->token;
	last_heredoc_file = NULL;
	while (tokens)
	{
		if (tokens->heredoc && falg)
		{
			if (last_heredoc_file)
				unlink(last_heredoc_file);
			last_heredoc_file = heredoc(tokens->file);
		} 
		if (tokens->append || tokens->intput || tokens->output)
		{
			if (!handle_redirections(tokens))
				return (0);
		}
		tokens = tokens->next;
	}
	if (last_heredoc_file)
	{
		int fd = open(last_heredoc_file, O_RDONLY);
		if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
			exit(1);
		close(fd);
		unlink(last_heredoc_file);
	}
	return (1);
}

void ft_execute(t_mini *mini)
{	
	mini->paths = ft_split(get_env_value(mini, "PATH"), ':');
	if (mini->pipe)
	{
		execute_pipeline(mini);
		return ;
	}
	if (!check_type(mini, 1))
		return ;
	if (is_builtin(mini->parss->cmd[0]))
		execute_builtin(mini->parss->cmd, mini);
	else
		execute_cmd(mini->parss->cmd, mini);
}
