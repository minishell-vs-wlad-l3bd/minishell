#include "../main/minishell.h"


int get_type(char *str)
{
	if (!str)
		return 0;
	return (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") ||
			!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"));
}

void	init_redir(t_tokens *head, char *str)
{
	int i;

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

char **list_to_array(t_list *lst, t_garbege **head)
{
    int size = ft_lstsize(lst);
    char **arr = ft_calloc(size + 1, sizeof(char *), head);
    int i = 0;

    if (!arr)
        return NULL;
    while (lst)
    {
        arr[i++] = lst->content;
        lst = lst->next;
    }
    arr[i] = NULL;
    return arr;
}

void	handle_argument(t_list **cmd_list, char *str, t_mini *mini, t_garbege **head)
{
	char	*expanded;
	char	**tmp;
	int		j;

	if (ft_strchr(str, '$') && !check_quotes_expand(str, mini))
	{
		expanded = expand_string(str, mini, head);
		if (!expanded)
			return ;
		tmp = split(expanded, 0, head);
		if (!tmp)
			return ;
		j = 0;
		while (tmp[j])
		{
			remove_quotes(tmp[j]);
			ft_lstadd_back(cmd_list, ft_lstnew(ft_strdup(tmp[j++], head), head));
		}
	}
	else
	{
		if (mini->parss && mini->parss->is_expand)
			str++;
		remove_quotes(str);
		ft_lstadd_back(cmd_list, ft_lstnew(ft_strdup(str, head), head));
	}
}

int	handle_redir(char **str, int *i, t_parsing *node, t_tokens **last, t_mini *mini, t_garbege **head)
{
	t_tokens	*new;

	new = ft_calloc(1, sizeof(t_tokens), head);
	if (!new)
		return (0);
	init_redir(new, str[*i]);
	if (str[*i + 1])
	{
		if (new->heredoc)
			new->file = ft_strdup(str[*i + 1], head);
		else if (ft_strchr(str[*i + 1], '$'))
			new->file = expand_string(str[*i + 1], mini, head);
		else
			new->file = ft_strdup(str[*i + 1], head);
		if (!new->file)
		{
			*i += 2;
			return (1);
		}
		remove_quotes(new->file);
		(*i)++;
	}
	if (!node->token)
		node->token = new;
	else
		(*last)->next = new;
	*last = new;
	return (1);
}


t_parsing	*init_all(char **str, t_mini *mini, t_garbege **head)
{
	t_parsing	*node;
	t_list		*cmd_list;
	t_tokens	*last;
	int			i;

	node = ft_calloc(1, sizeof(t_parsing), head);
	if (!node)
		return (NULL);
	cmd_list = NULL;
	last = NULL;
	i = 0;
	while (str[i])
	{
		if (get_type(str[i]) && str[i + 1])
		{
			if (!handle_redir(str, &i, node, &last, mini, head))
				return (NULL);
		}
		else
			handle_argument(&cmd_list, str[i], mini, head);
		i++;
	}
	node->cmd = list_to_array(cmd_list, head);
	return (node);
}

void    valid_syntax(char *line, t_mini *mini, t_garbege **head)
{
	char		**pipes;
	char		**redir;
	int			i;
	t_parsing	*node;
	t_parsing	*new;
	char		*spaces;

	node = NULL;
	mini->pipe = 0;
	i = 0;
	pipes = split_by_pipe(line, mini, head);
	while (pipes[i])
	{
		spaces = add_spaces(pipes[i], head);
        redir = split(spaces, 1, head);
        new = init_all(redir, mini, head);
        ft_lstadd_back_2(&node, new);
        i++;
    }
    mini->parss = node;
}
