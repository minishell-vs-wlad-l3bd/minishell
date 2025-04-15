#include "../minishell.h"

// void ft_free(void *ptr, int flag)
// {
//     static void *collecter[INT_MAX];
//     static int i;
//     int j;

//     if (flag)
//     {
//         j = 0;
//         while(collecter[j])
//             free(collecter[j++]);
//     }
//     else
//         collecter[i++] = ptr;
// }

void *ft_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
        exit(2);
    // ft_free(ptr, 0);
    return (ptr);
}
