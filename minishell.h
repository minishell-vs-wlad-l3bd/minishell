#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <limits.h>
#include "Libft/libft.h"

#define RED "\033[31m"
#define RESET "\033[0m"
#define BLEU "\033[34m"

#define mini "BLEU minishell\033[0m \033[31m▶ \033[0m" // hada macro dyal smiya dyal minishell n09dro nbdloh mn hna


typedef struct s_env
{
    char *value;
    struct s_env *next;
}   t_env;


typedef struct s_mini
{
    int in;
    int out;
    int ret; // return
} t_mini;


char	*find_cmd_path(char **paths, char *cmd);
char	*get_env_value(t_env *env, char *key);

// built in
void    do_cd(char **cmd, t_env **env);
void    do_echo(char **av);
void    quotes(char **strs);
void    do_unset(char **args, t_env **envp);
void	do_env(t_env *env);

void do_pwd(void);
void do_export(char **args, t_env **env);

void	do_exit(char **args, t_env **envp);




// for init env (kan3mr env->value)
t_env	*ft_env_lstnew(void *content);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_init(char **env);

void update_env(t_env **env, char *key, char *value);

// utils
void *ft_malloc(size_t size);
#endif