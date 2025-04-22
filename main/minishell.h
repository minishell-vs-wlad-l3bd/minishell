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
#include "../Libft/libft.h"
#include "../excute/excute.h"

#define RED "\033[31m"
#define RESET "\033[0m"
#define BLEU "\033[34m"

#define MAX_PATH 4096

typedef struct s_env
{
	char *key;
	char *value;
	int is_export;
	struct s_env *next;
}   t_env;

typedef enum e_redir
{
	R_NONE,
	R_IN,      // <
	R_OUT,     // >
	R_APPEND,  // >>
	R_PIPE,
}   t_redir;


typedef struct s_mini
{
	t_env	*env;
	t_env	*export_env;
	int		in;
	int		out;
	int		ret;
	int		exit;
	pid_t	pid;
} t_mini;


char	*find_cmd_path(char **paths, char *cmd);
char	*get_env_value(t_mini *mini, char *key);


// excute fonction
pid_t execute(char **paths, char **cmd, t_mini *mini);
void	execute_builtin(char **cmd, t_mini *mini);
void ft_execute(t_mini *mini, char *str);
int is_builtin(char *str);

// for init env (kan3mr env->value)
t_env	*ft_env_lstnew(void *key, void *value, int n);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_init(char **env, int flag);
void update_env(t_mini *mini, char *key, char *value);


// utils
void *ft_malloc(size_t size);
void pipe_handle(char **cmds, char **paths, t_mini *mini);
void    quotes(char **strs);

//signals
void	handler(int sig);
void	handler_child(int sig);

#endif