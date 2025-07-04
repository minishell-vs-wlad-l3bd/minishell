/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:40:59 by aayad             #+#    #+#             */
/*   Updated: 2025/07/03 20:14:45 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char	*extract_name(char *str, t_garbege **head)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (NULL);
	if (ft_isdigit(str[0]))
		return (ft_strdup("1", head));
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

static char	*get_expanded_token(char *str,
	int *i, t_mini *mini, t_garbege **head)
{
	char	*var_name;
	char	*value;

	if (str[*i + 1] == '\0')
		return (ft_substr(str, (*i)++, 1, head));
	var_name = extract_name(&str[*i + 1], head);
	if (!var_name)
		return (NULL);
	value = expand_value(&str[*i + 1], mini, head);
	*i += ft_strlen(var_name) + 1;
	if (value)
		return (ft_strdup(value, head));
	return (ft_strdup("", head));
}

static char	*replace_quotes(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			str[i] = 6;
		else if (str[i] == '"')
			str[i] = 7;
		i++;
	}
	return (str);
}

char	*expand_string(char *str, t_mini *mini, t_garbege **head)
{
	char	*res;
	char	*tmp;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	res = ft_strdup("", head);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '$')
			tmp = ft_substr(str, i++, 1, head);
		else if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			tmp = get_expanded_token(str, &i, mini, head);
			tmp = replace_quotes(tmp);
		}
		else
			tmp = ft_substr(str, i++, 1, head);
		res = ft_strjoin(res, tmp, head);
	}
	mini->exit = 0;
	return (res);
}
