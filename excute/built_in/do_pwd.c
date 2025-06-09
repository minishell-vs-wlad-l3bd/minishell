/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:59 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/09 17:15:19 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"


void    do_pwd(t_mini *mini)
{
    char cwd[MAX_PATH];

    if (getcwd(cwd, sizeof(cwd)))
        printf("%s\n", cwd);
    else
        printf("%s\n", get_env_value(mini, "PWD"));
}
