/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:19:56 by mohidbel          #+#    #+#             */
/*   Updated: 2025/07/03 16:39:53 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

static void	setup_pipe_io(t_mini *mini, int is_first, int is_last)
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

static void	child_process_setup_io(t_mini *mini, t_parsing *parss,
				int i, int total_cmds)
{
	int	fd;

	setup_pipe_io(mini, i == 0, i == total_cmds - 1);
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
}

static void	child_process_exec(t_mini *mini, t_parsing *parss,
				t_garbege **head)
{
	char	*cmd_path;

	if (parss->cmd[0])
		if (!check_type(mini, 0, head, parss))
			exit(1);
	mini->ev = env_list_to_array(mini->env, head);
	if (is_builtin(parss->cmd[0]))
	{
		execute_builtin(parss->cmd, mini, head);
		exit(0);
	}
	else
	{
		cmd_path = find_cmd_path(mini->paths, parss->cmd[0], mini, head);
		if (!cmd_path)
			exit(mini->exit);
		exec_in_child(cmd_path, parss->cmd, mini);
	}
}

static int	fork_and_setup_processes(t_mini *mini, t_garbege **head,
				t_parsing *parss, pid_t *pids)
{
	int	i;
	int	count_cmds;

	count_cmds = ft_lstsize_pipe(parss);
	i = -1;
	while (++i < count_cmds)
	{
		if (i < count_cmds - 1)
		{
			if (!create_pipe(mini))
				return (0);
		}
		signal(SIGINT, SIG_IGN);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			child_process_setup_io(mini, parss, i, count_cmds);
			child_process_exec(mini, parss, head);
		}
		else if (pids[i] < 0)
			return (kill_all(mini->pids, i), fork_failed(mini));
		parent_cleanup(mini, i, count_cmds);
		parss = parss->next;
	}
	return (1);
}

void	execute_pipeline(t_mini *mini, t_garbege **head)
{
	t_parsing	*parss;
	int			count_cmds;

	parss = mini->parss;
	handle_empty_redirections(parss, mini);
	count_cmds = ft_lstsize_pipe(parss);
	if (!prepare_heredocs(mini, head))
		return ;
	mini->pids = ft_malloc(sizeof(pid_t) * count_cmds, head);
	if (!fork_and_setup_processes(mini, head, parss, mini->pids))
		return ;
	wait_for_children(mini->pids, count_cmds, mini);
	setup_parent_signals();
	cleanup_heredocs(mini->parss);
}
