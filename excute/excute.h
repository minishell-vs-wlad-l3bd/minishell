#ifndef EXCUTE_H
#define EXCUTE_H

#include "../main/minishell.h"

typedef struct s_mini t_mini;


// built in
void    do_cd(char **cmd, t_mini *mini);
void    do_echo(char **av);
void    do_unset(char **args, t_mini *mini);
void	do_env(t_mini *mini);
void	do_pwd(void);
void	do_export(char **args, t_mini *mini);
void	do_exit(char **args, t_mini *mini);


int handle_redirections(char **cmd);

#endif