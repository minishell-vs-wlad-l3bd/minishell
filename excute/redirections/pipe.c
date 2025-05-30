/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:19:56 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/30 16:16:02 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"


int ft_lstsize(t_parsing *parss)
{
    int i = 0;
    while(parss)
    {
        i++;
        parss = parss->next;
    }
    return i;
}

int create_pipe(t_mini *mini)
{
    int pipe_fds[2];

    if (pipe(pipe_fds) == -1)
    {
        perror("minishell: pipe failed");
        return 0;
    }
    mini->pipe_in = pipe_fds[0];
    mini->pipe_out = pipe_fds[1];
    return 1;
}

void prepare_heredocs(t_mini *mini)
{
    t_parsing *parss = mini->parss;
    while (parss)
    {
        t_tokens *tokens = parss->token;
        while (tokens)
        {
            if (tokens->heredoc)
            {
                if (parss->heredoc_file)
                    unlink(parss->heredoc_file);
                parss->heredoc_file = heredoc(mini, tokens->file);
                if (!parss->heredoc_file)
					return;
            }
            tokens = tokens->next;
        }
        parss = parss->next;
    }
}

void setup_pipe_io(t_mini *mini, int is_first, int is_last)
{
    if (!is_first)
    {
        dup2(mini->prev_pipe, STDIN_FILENO);
        close(mini->prev_pipe);
    }
    if (!is_last)
	{
        dup2(mini->pipe_out, STDOUT_FILENO);
		close(mini->pipe_out);
	}
  	close(mini->pipe_in);
}

char **remove_null_entries(char **cmd)
{
    int count = 0;
    int j = 0;
    int i = 0;
    while (cmd[count])
        count++;
    char **new_cmd = ft_calloc(count + 1, sizeof(char *));
    if (!new_cmd)
        return NULL;

    while (cmd[i])
    {
        if (cmd[i] != NULL)
            new_cmd[j++] = ft_strdup(cmd[i]);
        i++;
    }
    new_cmd[j] = NULL;
    return new_cmd;
}

static void	child_process(char *str, char **paths,
	t_mini *mini, t_parsing *parss, int i, int total_cmds)
{
	int fd;
	setup_pipe_io(mini, i == 0, i == total_cmds - 1);
	if (parss->heredoc_file)
	{
		fd = open(parss->heredoc_file, O_RDONLY);
		if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
		{
			// perror("minishell: heredoc dup2");
			exit(1);
		}
		close(fd);
	}
	if (!check_type(str, paths, mini, 0))
		exit(1);
	if (is_builtin(parss->cmd[0]))
	{
		execute_builtin(parss->cmd, mini);
		exit(0);
	}
	else
	{
		execute_cmd(paths, parss->cmd, mini);
		exit(0);
	}
}

static void parent_cleanup(t_mini *mini, int i, int total_cmds)
{
    if (mini->prev_pipe != -1) {
        close(mini->prev_pipe);
        mini->prev_pipe = -1;
    }
    if (i < total_cmds - 1)
        mini->prev_pipe = mini->pipe_in;
    else
        close(mini->pipe_in);
    close(mini->pipe_out);
}

void	execute_pipeline(char *str, char **paths, t_mini *mini)
{
	t_parsing	*parss;
	int			count_cmds;
	pid_t		*pids;
	int			i;

	parss = mini->parss;
	count_cmds = ft_lstsize(parss);
	prepare_heredocs(mini);
	i = -1;
    pids = ft_malloc(sizeof(pid_t) * count_cmds);
	while (++i < count_cmds)
	{
		if (i < count_cmds - 1 && !create_pipe(mini))
			return ;
		pids[i] = fork();
		if (pids[i] == 0)
			child_process(str, paths, mini, parss, i, count_cmds);
		else if (pids[i] < 0)
		{
			close(mini->pipe_in);
    		close(mini->pipe_out);
			return (perror("minishell: fork"));
		}
		parent_cleanup(mini, i, count_cmds);
		parss = parss->next;
	}
	setup_parent_signals();
	i = -1;
	while (++i < count_cmds)
		waitpid(pids[i], NULL, 0);
	parss = mini->parss;
	while (parss)
	{
		if (parss->heredoc_file)
		{
			unlink(parss->heredoc_file);
			parss->heredoc_file = NULL;
		}
		parss = parss->next;
	}
}
