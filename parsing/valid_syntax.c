/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:39:14 by aayad             #+#    #+#             */
/*   Updated: 2025/07/03 16:53:12 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	init_redir(t_tokens *head, char *str)
{
	int	i;

	i = 0;
	i = 0;
	if (str[i] == '<' && str[i + 1] == '<')
		head->heredoc = 1;
	else if (str[i] == '>' && str[i + 1] == '>')
		head->append = 1;
	else if (str[i] == '<')
		head->input = 1;
	else if (str[i] == '>')
		head->output = 1;
}

int	has_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (1);
		str++;
	}
	return (0);
}

int	handle_redir(char **str, int *i, t_parsing *node, t_tokens **last)
{
	t_tokens	*new;

	new = ft_calloc(1, sizeof(t_tokens), node->head);
	init_redir(new, str[*i]);
	if (str[*i + 1])
	{
		if (new->heredoc)
		{
			if (!has_quotes(str[*i + 1]))
				new->here_expand = 1;
			new->file = ft_strdup(str[*i + 1], node->head);
		}
		else if (ft_strchr(str[*i + 1], '$'))
			new->file = expand_string(str[*i + 1], node->mini, node->head);
		else
			new->file = ft_strdup(str[*i + 1], node->head);
		if (new->file)
			remove_quotes(new->file);
		(return_quote(&new->file), (*i)++);
	}
	if (!node->token)
		node->token = new;
	else
		(*last)->next = new;
	return (*last = new, 1);
}

static void	handle_pipe(char **pipes, t_mini *mini,
	t_garbege **head, t_parsing **node)
{
	char		**redir;
	char		*spaces;
	t_parsing	*new;
	int			i;

	i = 0;
	while (pipes[i])
	{
		spaces = add_spaces(pipes[i], head);
		redir = split(spaces, head);
		new = init_all(redir, mini, head);
		ft_lstadd_back_2(node, new);
		i++;
	}
}

void	valid_syntax(char *line, t_mini *mini, t_garbege **head)
{
	char		**pipes;
	t_parsing	*node;

	node = NULL;
	mini->pipe = 0;
	pipes = split_by_pipe(line, mini, head);
	handle_pipe(pipes, mini, head, &node);
	mini->parss = node;
}
