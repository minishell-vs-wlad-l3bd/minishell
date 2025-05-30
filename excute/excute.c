/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:44 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/30 10:17:08 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int is_builtin(char *str)
{
	remove_quotes(str);
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

void execute_builtin(char **cmd, t_mini *mini)
{
	// quotes(mini->parss->cmd);
	if (!strcmp(cmd[0], "cd"))
		do_cd(cmd, mini);
	else if(!strcmp(cmd[0], "echo"))
		do_echo(mini);
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

void execute_cmd(char **paths, t_parsing *parss, t_mini *mini)
{
	pid_t pid;
	char **check;
	int flag = 0;

	quotes(mini->parss->cmd);
	pid = fork();
	if (pid == 0)
	{
		if (mini->parss->is_expand)
		{
			child_flag = 1;
			if (!parss->expand[0])
				exit(0);
			char *cmd_path = find_cmd_path(paths, parss->expand[0]);
			if (!cmd_path)
			{
				printf("minishell: %s: command not found1\n", parss->expand[0]);
				mini->exit = 127;
				return ;
			}
			execve(cmd_path, parss->expand, mini->ev);
			printf("minishell: %s: command not found\n", parss->expand[0]);
			exit(127);
			child_flag = 0;
		}
		else
		{
			child_flag = 1;
			char *cmd_path = find_cmd_path(paths, parss->cmd[0]);
			if (!cmd_path)
			{
				printf("minishell: %s: command not found\n", parss->cmd[0]);
				mini->exit = 127;
				return ;
			}
			execve(cmd_path, parss->cmd, mini->ev);
			printf("minishell: %s: command not found\n", parss->cmd[0]);
			exit(127);
			child_flag = 0;
		}
	
	}
	else
		waitpid(pid, NULL, 0);
}


int check_type(char *str, char **paths, t_mini *mini, int falg)
{
	t_tokens *tokens = mini->parss->token;
	
	char *last_heredoc_file = NULL;

	while (tokens)
	{
		if (tokens->heredoc && falg)
		{
			remove_quotes(tokens->file);
			if (last_heredoc_file)
				unlink(last_heredoc_file);
			last_heredoc_file = heredoc(mini, tokens->file);
		}
		if (tokens->append || tokens->intput || tokens->output)
		{
			// remove_quotes(tokens->file);
			if (!handle_redirections(tokens))
				return 0;
		}
		tokens = tokens->next;
	}
	if (last_heredoc_file)
	{
		int fd = open(last_heredoc_file, O_RDONLY);
		if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell: heredoc dup2");
			exit(1);
		}
		close(fd);
		unlink(last_heredoc_file);
	}
	return 1;
}



void ft_execute(t_mini *mini, char *str)
{
	pid_t pid;
    char **paths;
	
    paths = ft_split(get_env_value(mini, "PATH"), ':');
    if (mini->pipe)
	{
        execute_pipeline(str, paths, mini);
        return ;
	}
    if(!check_type(str, paths, mini, 1))
		return ;
	if (!mini->parss->cmd[0])
		return ;
    if (is_builtin(mini->parss->cmd[0]))
        execute_builtin(mini->parss->cmd, mini);
    else
		execute_cmd(paths, mini->parss, mini);
}
