/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:35:04 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/09 13:14:37 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

static void remove_env_var(char *var, t_mini *mini)
{
    t_env *temp;
    t_env *prev;
    size_t len;
    
    temp = mini->env;
    prev = NULL;
    len  = ft_strlen(var);
    while (temp)
    {
        if (ft_strcmp(temp->key, var) == 0)
        {
            if (prev)
                prev->next = temp->next;
            else
                mini->env = temp->next;
            return ;
        }
        prev = temp;
        temp = temp->next;
    }
}

static int  is_invalid_identifier(char *str, t_mini *mini)
{
    int i;

    i = 0;
    if (!str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
    {
        ft_putendl_fd("unset: invalid identifier", STDERR_FILENO);
        mini->exit = 1;
        return (1);
    }
    while (str[++i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
        {
            ft_putendl_fd("unset: invalid identifier", STDERR_FILENO);
            mini->exit = 1;
            return (1);
        }
    }
    return (0);
}

void do_unset(char **args, t_mini *mini)
{
    int i;

    i = 0;
    while (args[i])
    {
        if (!is_invalid_identifier(args[i], mini))
            remove_env_var(args[i], mini);
        i++;
    }
}
