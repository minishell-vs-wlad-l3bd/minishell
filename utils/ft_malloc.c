#include "../minishell.h"

void    *ft_malloc(size_t bytes)
{
    static void    *ret;

    ret = malloc(bytes);
    if (ret == NULL)
    {
        printf("allocation is failled");
        return NULL;
    }
    return (ret);
}