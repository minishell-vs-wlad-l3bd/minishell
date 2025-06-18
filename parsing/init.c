/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:48:09 by aayad             #+#    #+#             */
/*   Updated: 2025/06/17 19:13:57 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char	**list_to_array(t_list *lst, t_garbege **head)
{
	int		size;
	char	**arr;
	int		i;

	i = 0;
	size = ft_lstsize(lst);
	arr = ft_calloc(size + 1, sizeof(char *), head);
	if (!arr)
		return (NULL);
	while (lst)
	{
		arr[i++] = lst->content;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	handle_split_case(t_list **cmd_list,
	char *str, t_mini *mini, t_garbege **head)
{
	char	*expanded;
	char	**tmp;
	int		j;

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
		ft_lstadd_back(cmd_list,
			ft_lstnew(ft_strdup(tmp[j++], head), head));
	}
}

void	handle_argument(t_list **cmd_list,
	char *str, t_mini *mini, t_garbege **head)
{
	if (ft_strchr(str, '$') && !check_quotes_expand(str, mini))
		handle_split_case(cmd_list, str, mini, head);
	else
	{
		if (mini->parss && mini->parss->is_expand)
			str++;
		remove_quotes(str);
		ft_lstadd_back(cmd_list, ft_lstnew(ft_strdup(str, head), head));
	}
}

t_parsing	*init_all(char **str, t_mini *mini, t_garbege **head)
{
	t_parsing	*node;
	t_list		*cmd_list;
	t_tokens	*last;
	int			i;

	node = ft_calloc(1, sizeof(t_parsing), head);
	node->mini = mini;
	node->head = head;
	cmd_list = NULL;
	last = NULL;
	i = 0;
	while (str[i])
	{
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
