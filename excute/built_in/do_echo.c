#include "../excute.h"

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
