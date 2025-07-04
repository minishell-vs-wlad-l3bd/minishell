/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:48:09 by aayad             #+#    #+#             */
/*   Updated: 2025/07/03 20:14:49 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

static void	handle_split_else_case(t_list **cmd_lst,
	char **tmp, t_garbege **head)
{
	int	j;

	j = 0;
	while (tmp[j])
	{
		remove_quotes(tmp[j]);
		return_quote(&tmp[j]);
		if (tmp[j][0] == '\0' && j != 0)
		{
			j++;
			continue ;
		}
		else
			ft_lstadd_back(cmd_lst, ft_lstnew(ft_strdup(tmp[j], head), head));
		j++;
	}
}

static void	handle_split_case(t_list **cmd_lst,
	char *str, t_mini *mini, t_garbege **head)
{
	char	*expanded;
	char	**tmp;

	expanded = expand_string(str, mini, head);
	if (mini->split)
	{
		remove_quotes(expanded);
		return_quote(&expanded);
		ft_lstadd_back(cmd_lst, ft_lstnew(ft_strdup(expanded, head), head));
	}
	else
	{
		tmp = split(expanded, head);
		if (!tmp)
			return ;
		handle_split_else_case(cmd_lst, tmp, head);
	}
}

static void	handle_argument(t_list **cmd_list,
	char *str, t_mini *mini, t_garbege **head)
{
	if (ft_strchr(str, '$') && !check_quotes_expand(str))
		handle_split_case(cmd_list, str, mini, head);
	else
	{
		remove_quotes(str);
		ft_lstadd_back(cmd_list, ft_lstnew(ft_strdup(str, head), head));
	}
}

static void	check_export_split(char **str, int i, t_mini *mini)
{
	mini->split = 0;
	if (!ft_strcmp(str[0], "export"))
	{
		if (str[i] && is_valid_env_name(str[i]))
			mini->split = 1;
	}
}

t_parsing	*init_all(char **str, t_mini *mini, t_garbege **head)
{
	t_parsing	*node;
	t_list		*cmd_list;
	t_tokens	*last;
	int			i;

	node = ft_calloc(1, sizeof(t_parsing), head);
	(1) && (node->mini = mini, node->head = head);
	cmd_list = NULL;
	last = NULL;
	i = 0;
	while (str[i])
	{
		check_export_split(str, i, mini);
		if (get_type(str[i]) && str[i + 1])
		{
			if (!handle_redir(str, &i, node, &last))
				return (NULL);
		}
		else
			handle_argument(&cmd_list, str[i], mini, head);
		i++;
	}
	node->cmd = list_to_array(cmd_list, head);
	return (node);
}
