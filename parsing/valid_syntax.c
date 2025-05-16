#include "../main/minishell.h"


int		get_type(char *str)
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

void init_redir(t_tokens *head, char *str)
{
	int i = 0;

	if (str[i] == '<' && str[i + 1] == '<')
		head->heredoc = 1;
	else if (str[i] == '>' && str[i + 1] == '>')
		head->append = 1;
	else if (str[i] == '<')
		head->intput = 1;
	else if (str[i] == '>')
		head->output = 1;
}

t_parsing *init_all(char **str)
{
	t_parsing *head;
	t_tokens *current_token;
	int i = 0;
	int in = 0;

	head = ft_malloc(sizeof(t_parsing));
	head->cmd = ft_malloc(sizeof(char *) * (double_arr_len(str) + 1));
	head->token = NULL;
	current_token = NULL;
	t_tokens *last_token = NULL;
	while (str[i])
	{
		if (get_type(str[i]) && !ft_strchr(str[i], '\'') && !ft_strchr(str[i], '\"'))
		{
			t_tokens *new_token = ft_calloc(1, sizeof(t_tokens));
			if (!new_token)
				return (NULL);
			init_redir(new_token, str[i]);
			if (str[i + 1])
			{
				new_token->file = str[i + 1];
				i++;
			}
			else
				new_token->file = NULL;
			if (!head->token)
				head->token = new_token;
			else
				last_token->next = new_token;

			last_token = new_token;
		}
		else
			head->cmd[in++] = str[i];
		i++;
	}
	head->cmd[in] = NULL;
	return head;
}


void    valid_syntax(char *line, t_mini *mini)
{
    char        **pipes;
    char        **redir;
    int            i = 0;
    t_parsing    *head = NULL;
    t_parsing    *new;
	char		*spaces;

    pipes = split_by_pipe(line);
    while (pipes[i])
    {
		// spaces = insert_spaces(pipes[i]);
        redir = ft_split(pipes[i], ' ');
        new = init_all(redir);
        ft_lstadd_back_2(&head, new);
        i++;
    }
    mini->parss = head;
}
