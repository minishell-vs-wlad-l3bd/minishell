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
#include <stdbool.h>
#include <dirent.h>

#define RED "\033[31m"
#define RESET "\033[0m"
#define BLEU "\033[34m"

#define MAX_PATH 4096

typedef struct tokens
{
	int		CMD;
	int     append;
    int     heredoc;
	int		intput;
	int		output;
	char 	*file;
	int		flag;
	struct tokens *next;
}	t_tokens;


typedef struct s_parsing
{
	char *heredoc_file;
	int		is_expand;
    char    **cmd;
    char    **expand; // 
	t_tokens *token;
	struct s_parsing	*next;
} t_parsing;

typedef struct s_heredoc {
    char *filename;
    struct s_heredoc *next;
} t_heredoc;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}   t_env;

typedef struct s_mini
{
	t_heredoc *heredocs;
	char	**ev;
	int		pipe;
	int		pipe_in;
	int		pipe_out;
	int		prev_pipe;
	int		flag_expand;
	int		in;
	int		out;
	int		ret;
	int		exit;
	pid_t	pid;
	t_env	*env;
	t_env	*export_env;
	t_parsing *parss;
} t_mini;


// for garbeg collectr
typedef struct s_node
{
	void            *ptr;
	struct s_node   *next;
}   t_node;




char *find_cmd_path(char **paths, char *cmd, t_mini *mini);
char	*get_env_value(t_mini *mini, char *key);
int		double_arr_len(char **str);
// excute fonction
void execute_cmd(char **paths, char **cmd, t_mini *mini);
void execute_builtin(char **cmd, t_mini *mini);
void	ft_execute(t_mini *mini, char *str);
int		is_builtin(char *str);

void    do_cd(char **cmd, t_mini *mini);
void do_echo(t_mini *mini);
void    do_unset(char **args, t_mini *mini);
void	do_env(t_mini *mini);
void	do_pwd(t_mini *mini);
void	do_export(char **args, t_mini *mini);
void	do_exit(char **args, t_mini *mini);
int		double_arr_len(char **str);
int check_type(char *str, char **paths, t_mini *mini, int flag);

void execute_pipeline(char *str, char **paths, t_mini *mini);
void    increment_shlvl(t_mini *mini);
char *heredoc(t_mini *mini, char *delimiter);

// for init env (kan3mr env->value)
t_env	*ft_env_lstnew(void *key, void *value);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_init(char **env, int flag);
void	update_env(t_env **env, char *key, char *value);
char *expand_string(char *str, t_mini *mini);

// utils
void *ft_malloc(size_t size);
void ft_free_all(void);
void    quotes(char **strs);

//signals
void setup_child_signals(void);
void setup_parent_signals(void);
// void	handler(int sig);
void	handler_heredoc(int sig);
void disable_echoctl(void);
void    reset_std_fds(t_mini *mini);
void    backup_std_fds(t_mini *mini);

int			ft_isspace(char c);
int			valid_line(char *line);
int			check_quotes(char *line);
int			check_syntax(char *str);
int			analys_syntax(char *line);
void    	valid_syntax(char *line, t_mini *mini);
void		ft_lstadd_back_2(t_parsing **lst, t_parsing *new);
char		**split_by_pipe(const char *s, t_mini *mini);
int			check_input(char *str, t_mini *mini);


int handle_redirections(t_tokens *token);
char	*add_spaces(char *line);
char		**split(char const *s, char c);
void replace_expand_to_value(t_mini *mini);
char **env_list_to_array(t_env *env);
void	remove_quotes(char *str);

int	check_redir_sequence(char *str, int *i);
int	mixed_redirection_error(char *str);
int	redir_syntax_error(char *str);
int	check_quotes_expand(char *str, t_mini *mini);


#endif //MINISHELL_H