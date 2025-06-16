/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:30:11 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/16 13:29:23 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <termios.h>
# include "../Libft/libft.h"
# include <stdbool.h>
# include <dirent.h>

# define MAX_PATH 4096

extern int	g_check_signal;

typedef struct tokens
{
	int				append;
	int				heredoc;
	int				input;
	int				output;
	char			*file;
	struct tokens	*next;
}	t_tokens;

typedef struct s_parsing
{
	char				*heredoc_file;
	int					is_expand;
	char				**cmd;
	t_tokens			*token;
	struct s_parsing	*next;
}	t_parsing;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_mini
{
	int			pipe;
	int			pipe_in;
	int			pipe_out;
	int			prev_pipe;
	int			in;
	int			out;
	int			exit;
	char		**ev;
	char		**paths;
	t_env		*env;
	t_env		*export_env;
	t_parsing	*parss;
}	t_mini;

char	*find_cmd_path(char **paths, char *cmd, t_mini *mini, t_garbege **head);
char	*get_env_value(t_mini *mini, char *key);
void	execute_builtin(char **cmd, t_mini *mini, t_garbege **head);
void	ft_execute(t_mini *mini, t_garbege **head);
int		is_builtin(char *str);
void	do_cd(char **cmd, t_mini *mini, t_garbege **head);
void	do_echo(t_mini *mini, t_garbege **head);
void	do_unset(char **args, t_mini *mini);
void	do_env(t_mini *mini, t_garbege **head);
void	do_pwd(t_mini *mini);
void	do_export(char **args, t_mini *mini, t_garbege **head);
void	do_exit(char **args, t_mini *mini, t_garbege **head);
int		check_type(t_mini *mini, int falg, t_garbege **head);
void	execute_pipeline(t_mini *mini, t_garbege **head);
void	increment_shlvl(t_mini *mini, t_garbege **head);
char	*heredoc(char *delimiter, t_mini *mini, t_garbege **head);
t_env	*ft_env_lstnew(void *key, void *value, t_garbege **head);
void	ft_env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_init(char **env, int flag, t_garbege **head);
void	update_env(t_env **env, char *key, char *value, t_garbege **head);
char	*expand_string(char *str, t_mini *mini, t_garbege **head);
void	*ft_malloc(size_t size, t_garbege **head);
void	ft_free_all(t_garbege **head);
void	remove_quotes(char *str);
void	setup_child_signals(void);
void	setup_parent_signals(void);
void	handler_heredoc(int sig);
void	disable_echoctl(void);
int		ft_isspace(char c);
int		valid_line(char *line, t_mini *mini);
int		check_quotes(char *line);
int		check_syntax(char *str);
int		analys_syntax(char *line, t_mini *mini);
void	valid_syntax(char *line, t_mini *mini, t_garbege **head);
void	ft_lstadd_back_2(t_parsing **lst, t_parsing *new);
char	**split_by_pipe(const char *s, t_mini *mini, t_garbege **head);
int		check_input(char *str, t_mini *mini, t_garbege **head);
int		handle_redirections(t_tokens *token, t_mini *mini);
char	*add_spaces(char *line, t_garbege **head);
char	**split(const char *s, int use_quote, t_garbege **head);
char	**env_list_to_array(t_env *env, t_garbege **head);
int		check_quotes_expand(char *str, t_mini *mini);
void	ft_sort(t_mini *mini);
void	print_sort_env(t_mini *mini);
int		check_is_key(t_env **env, char *key);
void	exec_in_child(char *cmd_path, char **cmd, t_mini *mini);
void	handle_child_status(int status, t_mini *mini);
int		is_directory(char *cmd);
void	enable_echoctl(void);
int 	handle_heredoc_token(t_tokens *tok, t_mini *mini,
					t_garbege **head, char **last_file);
int		handle_all_redirections(t_tokens *tokens, t_mini *mini);
void	wait_for_children(pid_t *pids, int count_cmds, t_mini *mini);
void	cleanup_heredocs(t_parsing *parss);
int		ft_lstsize_pipe(t_parsing *parss);
int		create_pipe(t_mini *mini);
void	parent_cleanup(t_mini *mini, int i, int total_cmds);
void	prepare_heredocs(t_mini *mini, t_garbege **head);
int 	fork_failed(t_mini *mini);

#endif 