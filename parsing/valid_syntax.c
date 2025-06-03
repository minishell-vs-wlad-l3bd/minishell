/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:31:52 by aayad             #+#    #+#             */
/*   Updated: 2025/05/31 14:36:56 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	get_type(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (ft_strnstr(str, ">>", len))
		return (1);
	if (ft_strnstr(str, "<<", len))
		return (1);
	if (ft_strchr(str, '>'))
		return (1);
	if (ft_strchr(str, '<'))
		return (1);
	return (0);
}

void	init_redir(t_tokens *head, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<' && str[i + 1] == '<')
		head->heredoc = 1;
	else if (str[i] == '>' && str[i + 1] == '>')
		head->append = 1;
	else if (str[i] == '<')
		head->intput = 1;
	else if (str[i] == '>')
		head->output = 1;
}

static t_tokens	*create_token(char **str, int *i, t_mini *mini)
{
	t_tokens	*new;

	new = ft_malloc(sizeof(t_tokens));
	init_redir(new, str[*i]);
	remove_quotes(str[*i + 1]);
	if (str[*i + 1] && str[*i + 1][0] == '$' && !new->heredoc)
	{
		new->file = get_env_value(mini, str[*i + 1] + 1);
	}
	else if (str[*i + 1])
	{
		new->file = str[*i + 1];
		(*i)++;
	}
	return (new);
}

t_parsing	*init_all(char **str, t_mini *mini)
{
	t_parsing	*head;
	t_tokens	*last;
	int			i;
	int			in;
	t_tokens	*new;

	i = 0;
	in = 0;
	head = ft_malloc(sizeof(t_parsing));
	head->cmd = ft_malloc(sizeof(char *) * (double_arr_len(str) + 1));
	head->token = NULL;
	last = NULL;
	while (str[i])
	{
		if (get_type(str[i]) && !ft_strchr(str[i], '\'') && !ft_strchr(str[i], '\"'))
		{
			new = create_token(str, &i, mini);
			if (!head->token)
				head->token = new;
			else
				last->next = new;
			last = new;
		}
		else
			head->cmd[in++] = str[i];
		i++;
	}
	head->cmd[in] = NULL;
	return (head);
}

void	valid_syntax(char *line, t_mini *mini)
{
	char		**pipes;
	char		**redir;
	int			i;
	t_parsing	*head;
	t_parsing	*new;
	char		*spaces;

	head = NULL;
	mini->pipe = 0;
	i = 0;
	pipes = split_by_pipe(line, mini);
	while (pipes[i])
	{
		spaces = add_spaces(pipes[i]);
		redir = split(spaces, ' ');
		new = init_all(redir, mini);
		ft_lstadd_back_2(&head, new);
		i++;
	}
	mini->parss = head;
}
