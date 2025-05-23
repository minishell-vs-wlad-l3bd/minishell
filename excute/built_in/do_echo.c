/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:39 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/23 14:12:37 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"


void    do_echo(char **av)
{
    int     i;
    int     nl;
    int     j;

    i = 1;
    nl = 0;
    quotes(av);
    while (av[i] && ft_strncmp(av[i], "-n", 2) == 0)
    {
        j = 2;
        while (av[i][j] == 'n')
            j++;
        if (av[i][j] != '\0')
            break ;
        nl++;
        i++;
    }
    while (av[i])
    {
        ft_putstr_fd(av[i], STDOUT_FILENO);
        if (av[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (!nl)
        ft_putchar_fd('\n', STDOUT_FILENO);
}
