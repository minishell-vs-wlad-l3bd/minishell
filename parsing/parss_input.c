#include "../main/minishell.h"

int		special_char(char *line)
{
	int		i;
	int		skip;

	i = 0;
	while (line[i])
	{
		skip = check_quotes(&line[i]);
		if (skip > 0)
			i += skip;
		else
			if (line[i] == ';' || line[i] == '\\' || line[i] == '&')
				return (1);
		i++;
	}
	return (0);
}

int		incorect_quotes(char *line)
{
	int	i = 0;
	char	q;

	while (line && line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			q = line[i];
			i++;
			while (line[i] && line[i] != q)
				i++;
			if (!line[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int		valid_line(char *line)
{
	if (special_char(line))
		return (ft_putendl_fd("Error : d'ont seport special char", 2), 0);
	if (incorect_quotes(line))
		return (ft_putendl_fd("Error : incorect quotes", 2), 0);
	if (!analys_syntax(line))
		return (0);
	return (1);
}

int		check_input(char *str, t_mini *mini)
{
	
	if (valid_line(str))
		valid_syntax(str, mini);
	else 
		return 1;
	return (0);
}
// void print_result(t_parsing *parss)
// {
// 	int i;
// 	t_tokens *tok;

// 	while (parss)
// 	{
// 		tok = parss->token;
// 		i = 0;
// 		printf("=====><======another node in parssing=====><=====\n");
// 		printf("===> Commands:\n");
// 		while (parss->cmd && parss->cmd[i])
// 		{
// 			printf("CMD[%d]: %s\n", i, parss->cmd[i]);
// 			i++;
// 		}
// 		while (tok)
// 		{
// 			printf("======another node in tokens=====\n");
// 			printf("\n===> Redirections:\n");
// 			printf("append : %d\n", tok->append);
// 			printf("heredoc : %d\n", tok->heredoc);
// 			printf("output : %d\n", tok->output);
// 			printf("intput : %d\n", tok->intput);
// 			printf("file : %s\n", tok->file);
// 			tok = tok->next;
// 		}
// 		parss = parss->next;
// 	}
// }
