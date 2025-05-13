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
#include <termios.h>
#include "../Libft/libft.h"
#include "../excute/excute.h"
#include <stdbool.h>

#define RED "\033[31m"
#define RESET "\033[0m"
#define BLEU "\033[34m"

#define MAX_PATH 4096

int child_flag;

typedef struct tokens
{
	int		CMD;
	int     append;
    int     heredoc;
	int		pipe;
	int		intput;
	int		output;
	char 	*file;
	int		flag;
	struct tokens *next;
}	t_tokens;


typedef struct s_parsing
{
    char    **cmd;
	t_tokens *token;
	struct s_parsing	*next;
} t_parsing;



typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}   t_env;

typedef struct s_mini
{
	char	**ev;
	int		pipe_in;
	int		pipe_out;
	int		prev_pipe;
	int		in;
	int		out;
	int		ret;
	int		exit;
	pid_t	pid;
	t_env	*env;
	t_env	*export_env;
	t_parsing *parss;
} t_mini;

char	*find_cmd_path(char **paths, char *cmd);
char	*get_env_value(t_mini *mini, char *key);
int		double_arr_len(char **str);
// excute fonction
void	execute_cmd(char **paths, char **cmd, t_mini *mini);
void	execute_builtin(char **cmd, t_mini *mini);
void	ft_execute(t_mini *mini, char *str);
int		is_builtin(char *str);

// for init env (kan3mr env->value)
t_env	*ft_env_lstnew(void *key, void *value);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_init(char **env, int flag);
void	update_env(t_env **env, char *key, char *value);

// utils
void *ft_malloc(size_t size);
void    quotes(char **strs);

//signals
void	handler(int sig);
void disable_echoctl(void);
void	handler_child(int sig);
void    reset_std_fds(t_mini *mini);
void    backup_std_fds(t_mini *mini);

int			ft_isspace(char c);
int			valid_line(char *line);
int			check_quotes(char *line);
int			check_syntax(char *str);
int			analys_syntax(char *line);
void    	valid_syntax(char *line, t_mini *mini);
void		ft_lstadd_back_2(t_parsing **lst, t_parsing *new);
char		**split_by_pipe(const char *s);
int			check_input(char *str, t_mini *mini);
#endif