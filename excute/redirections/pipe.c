/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:19:56 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/09 16:12:34 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"


int ft_lstsize_pipe(t_parsing *parss)
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

void prepare_heredocs(t_mini *mini, t_garbege **head)
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
                parss->heredoc_file = heredoc(tokens->file, mini, head);
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

static void	child_process(t_mini *mini, t_parsing *parss, int i, int total_cmds, t_garbege **head)
{
	int fd;

	if (!parss->cmd || !parss->cmd[0])
		exit(0);
	setup_pipe_io(mini, i == 0, i == total_cmds - 1);
	setup_child_signals();
	if (parss->heredoc_file)
	{
		fd = open(parss->heredoc_file, O_RDONLY);
		if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell: heredoc dup2");
			exit(1);
		}
		close(fd);
	}
	if (!check_type(mini, 0, head))
		exit(1);
	char *cmd_path;

	cmd_path = find_cmd_path(mini->paths, parss->cmd[0], mini, head);

	mini->ev=env_list_to_array(mini->env, head);
	if (is_builtin(parss->cmd[0]))
	{
		execute_builtin(parss->cmd, mini, head);
		exit(mini->exit);
	}
	else
	{	if (!cmd_path)
			exit(127);
		execve(cmd_path, parss->cmd, mini->ev);
		perror("minishell: ");
		exit(errno);
	}
}

void parent_cleanup(t_mini *mini, int i, int total_cmds)
{
	if (mini->prev_pipe != -1)
		close(mini->prev_pipe);

	if (i < total_cmds - 1)
		mini->prev_pipe = mini->pipe_in;
	else
		mini->prev_pipe = -1;

	if (mini->pipe_out != -1)
		close(mini->pipe_out);
}


void	execute_pipeline(t_mini *mini, t_garbege **head)
{
	t_parsing	*parss;
	int			count_cmds;
	pid_t		*pids;
	int			i;
	int			status;

	parss = mini->parss;
	count_cmds = ft_lstsize_pipe(parss);
	prepare_heredocs(mini, head);
	i = -1;
    pids = ft_malloc(sizeof(pid_t) * count_cmds, head);
	while (++i < count_cmds)
	{
		if (i < count_cmds - 1 && !create_pipe(mini))
			return ;
		signal(SIGINT, SIG_IGN);
		pids[i] = fork();
		if (pids[i] == 0)
			child_process(mini, parss, i, count_cmds, head);
		else if (pids[i] < 0)
		{
			close(mini->pipe_in);
    		close(mini->pipe_out);
			return (perror("minishell: fork"));
		}
		parent_cleanup(mini, i, count_cmds);
		parss = parss->next;
	}
	i = -1;
	while (++i < count_cmds)
		waitpid(pids[i], &status, 0);
	if (WIFEXITED(status))
		mini->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		else if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		mini->exit = 128 + WTERMSIG(status);
	}
	setup_parent_signals();
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
