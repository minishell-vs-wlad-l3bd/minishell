#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> // hado 7it kaytl3 liya error f windowz
#include <sys/wait.h> // same thing (waitpid)
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <limits.h>
#include "Libft/libft.h"

#define mini "\033[34mminishell\033[0m \033[31m▶ \033[0m" // hada macro dyal smiya dyal minishell n09dro nbdloh mn hna


typedef struct s_env
{
    char *value;
    struct s_env *next;
}   t_env;
// hadi ghir bash nchd env 7it ghan7tajoh bash n handli env command


char	*find_cmd_path(char **paths, char *cmd);
char	*get_env_value(t_env *env, char *key);

// built in
void    do_cd(char **cmd, t_env **env);
void    do_echo(char **av);
void    quotes(char **strs);
void    do_unset(char **args, t_env **envp);
void	do_env(t_env *env);
void	do_exit(char **args, t_env **envp);



// for init env (kan3mr env->value)
t_env	*ft_env_lstnew(void *content);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_init(char **env);

int     handle_redirections(char **cmd);

#endif