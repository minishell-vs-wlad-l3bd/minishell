/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:40:59 by aayad             #+#    #+#             */
/*   Updated: 2025/06/17 20:21:20 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char	*extract_name(char *str, t_garbege **head)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (NULL);
	if (str[i] == '?')
		return (ft_strdup("?", head));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i, head));
}

char	*expand_value(char *str, t_mini *mini, t_garbege **head)
{
	char	*var_name;
	char	*value;
	int		i;

	var_name = extract_name(str, head);
	value = NULL;
	i = 0;
	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
		value = ft_itoa(mini->exit, head);
	else
		value = get_env_value(mini, var_name);
	if (value)
		return (ft_strdup(value, head));
	else
		return (NULL);
}

static char	*prepare_and_expand(char *result, char *var_start,
		t_mini *mini, t_garbege **head)
{
	char	*var_name;
	char	*value;
	char	*before;
	char	*after;
	char	*joined;

	var_name = extract_name(var_start + 1, head);
	if (!var_name)
		return (NULL);
	value = expand_value(var_start + 1, mini, head);
	before = ft_substr(result, 0, var_start - result, head);
	if (!before)
		return (NULL);
	after = ft_strdup(var_start + 1 + ft_strlen(var_name), head);
	if (!after)
		return (NULL);
	joined = ft_strjoin(before, value, head);
	if (!joined)
		return (NULL);
	return (ft_strjoin(joined, after, head));
}

char	*expand_string(char *str, t_mini *mini, t_garbege **head)
{
	char	*result;
	char	*var_start;
	char	*new_result;

	if (!str)
		return (NULL);
	result = ft_strdup(str, head);
	var_start = ft_strchr(result, '$');
	while (var_start)
	{
		new_result = prepare_and_expand(result, var_start, mini, head);
		if (!new_result)
			return (NULL);
		result = new_result;
		var_start = ft_strchr(result, '$');
	}
	return (result);
}
