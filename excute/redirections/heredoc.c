/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:25 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/08 16:33:57 by mohidbel         ###   ########.fr       */
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
        return (NULL);
    file = ft_strjoin("/tmp/heredoc_", pid_str);
    if (!file)
        return (NULL);
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (NULL);
    close(fd);
    return (file);
}

char *heredoc(char *delimiter)
{
    pid_t pid;
    char *filename;
    int fd;
    char *line;
    int status;

    filename = get_temp_file();
    if (!filename || !delimiter)
        return (NULL);
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (NULL);
    pid = fork();
    if (pid == -1)
        return (close(fd), NULL);
    if (pid == 0)
    {
        signal(SIGINT, handler_heredoc);
        while (1)
        {
            line = readline("> ");
            if (!line)
                exit(0);
            if (!ft_strcmp(line, delimiter))
                exit(0);
            ft_putendl_fd(line, fd);
        }
    }
    close(fd);
    signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    setup_parent_signals();
    if (WIFEXITED(status))
    g_exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_exit_status = 128 + WTERMSIG(status);
    if (WIFSIGNALED(status))
        return (unlink(filename), NULL);
    return (filename);
}
