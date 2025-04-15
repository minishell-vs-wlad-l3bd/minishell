#include "../minishell.h"

void    do_echo(char **av)
{
    int     i;
    int     nl;
    int     j;

    i = 0;
    nl = 0;
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
        write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
        if (av[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (!nl)
        write(STDOUT_FILENO, "\n", 1);
}
