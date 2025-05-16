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
	current_token = ft_malloc(sizeof(t_tokens));
	if (!head || !current_token)
		return (NULL);
	head->cmd = ft_malloc(sizeof(char *) * double_arr_len(str) + 1);
	if (!head->cmd)
		return (NULL); 
	head->token = current_token;
	while (str[i])
	{
		if (get_type(str[i]) && !ft_strchr(str[i], '\'') && !ft_strchr(str[i], '\"'))
		{
			init_redir(current_token, str[i]);
			if (str[i + 1])
			{
				current_token->file = str[i + 1];
				i++;
			}
			current_token->next = ft_malloc(sizeof(t_tokens));
			if (!current_token->next)
				return (NULL);
			current_token = current_token->next;
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

	mini->pipe = 0;
    pipes = split_by_pipe(line, mini);
	// printf("pipe is =====>%d\n", mini->pipe);
    while (pipes[i])
    {
		// spaces = add_spaces(pipes[i]);
        redir = split(pipes[i], ' ');
        new = init_all(redir);
        ft_lstadd_back_2(&head, new);
        i++;
    }
    mini->parss = head;
	// // just for debug
	// int k = 0;
	// while(mini->parss)
	// {
	// 	for(int i = 0; mini->parss->cmd[i]; i++)
	// 		printf("command is : ==>%d, %s\n", k, mini->parss->cmd[i]); 
	// 	k++;
	// 	mini->parss = mini->parss->next;
	// }
}
