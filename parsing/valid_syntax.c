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
		head->intput = 1;
	else if (str[i] == '>')
		head->output = 1;
}

char **list_to_array(t_list *lst)
{
    int size = ft_lstsize(lst);
    char **arr = ft_calloc(size + 1, sizeof(char *));
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

void	handle_argument(t_list **cmd_list, char *str, t_mini *mini)
{
	char	*expanded;
	char	**tmp;
	int		j;

	if (ft_strchr(str, '$') && !check_quotes_expand(str, mini))
	{
		expanded = expand_string(str, mini);
		if (!expanded)
			return ;
		tmp = split(expanded, 0);
		if (!tmp)
			return ;
		j = 0;
		while (tmp[j])
		{
			remove_quotes(tmp[j]);
			ft_lstadd_back(cmd_list, ft_lstnew(ft_strdup(tmp[j++])));
		}
	}
	else
	{
		if (mini->parss && mini->parss->is_expand)
			str++;
		remove_quotes(str);
		ft_lstadd_back(cmd_list, ft_lstnew(ft_strdup(str)));
	}
}

int	handle_redir(char **str, int *i, t_parsing *head, t_tokens **last, t_mini *mini)
{
	t_tokens	*new;

	new = ft_calloc(1, sizeof(t_tokens));
	if (!new)
		return (0);
	init_redir(new, str[*i]);
	if (str[*i + 1])
	{
		if (ft_strchr(str[*i + 1], '$'))
			new->file = expand_string(str[*i + 1], mini);
		else
			new->file = ft_strdup(str[*i + 1]);
		if (!new->file)
		{
			*i += 2;
			return (1);
		}
		(*i)++;
	}
	if (!head->token)
		head->token = new;
	else
		(*last)->next = new;
	*last = new;
	return (1);
}

t_parsing	*init_all(char **str, t_mini *mini)
{
	t_parsing	*head;
	t_list		*cmd_list;
	t_tokens	*last;
	int			i;

	head = ft_calloc(1, sizeof(t_parsing));
	if (!head)
		return (NULL);
	cmd_list = NULL;
	last = NULL;
	i = 0;
	while (str[i])
	{
		if (get_type(str[i]))
		{
			if (!handle_redir(str, &i, head, &last, mini))
				return (NULL);
		}
		else
			handle_argument(&cmd_list, str[i], mini);
		i++;
	}
	head->cmd = list_to_array(cmd_list);
	return (head);
}

void    valid_syntax(char *line, t_mini *mini)
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
        redir = split(spaces, 1);
        new = init_all(redir, mini);
        ft_lstadd_back_2(&head, new);
        i++;
    }
    mini->parss = head;
}
