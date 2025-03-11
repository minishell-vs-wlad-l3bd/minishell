#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

char	*find_cmd_path(char **paths, char *cmd);
char	*find_path(char **env);


#endif