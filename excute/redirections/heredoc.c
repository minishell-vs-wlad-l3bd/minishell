/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:25 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/24 14:15:59 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"


char *get_temp_file(void)
{
    char *file;
    int fd;
    char *pid_str;

    pid_str = ft_itoa(getpid());
    if (!pid_str)
        return NULL;
    file = ft_strjoin("/tmp/heredoc_", pid_str);
    if (!file)
        return NULL;
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return NULL;
    close(fd);
    return file;
}

char *heredoc(t_mini *mini, char *delimiter)
{
    pid_t pid;
    char *filename = get_temp_file();
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char *line;
    int status;

    if (!filename || fd == -1 || !delimiter)
        return NULL;
    pid = fork();
    signal(SIGINT, SIG_IGN);
    if (pid == 0)
    {
        while (1)
        {
            signal(SIGINT, handler_heredoc);
            line = readline("> ");
            if (!line)
                break;
            if (!ft_strcmp(line, delimiter))
            {
                close(fd);
                exit(0);
            }
            ft_putendl_fd(line, fd);
        }
        close(fd);
    }
    waitpid(pid, &status, 0);
    mini->exit = WEXITSTATUS(status);
    setup_parent_signals();
    return filename;
}
