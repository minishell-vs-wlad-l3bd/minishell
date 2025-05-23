#include "../main/minishell.h"

void ft_free_all(void)
{
    static t_node *head;
    t_node *tmp;
    t_node *to_free;

	
    tmp = head;
    while (tmp)
    {
        free(tmp->ptr);
        to_free = tmp;
        free(to_free);
        tmp = tmp->next;
    }
    head = NULL;
}

void *ft_malloc(size_t size)
{
    static t_node *head;
    t_node *new_node;
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        ft_free_all();
        exit(2);
    }
    new_node = malloc(sizeof(t_node));
    if (!new_node)
    {
        free(ptr);
        exit(2);
    }
    new_node->ptr = ptr;
    new_node->next = head;
    head = new_node;
    return ptr;
}

