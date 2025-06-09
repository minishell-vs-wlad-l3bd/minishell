/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:25 by mohidbel          #+#    #+#             */
/*   Updated: 2025/06/09 16:35:26 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"


char *get_temp_file(t_garbege **head)
{
    char *file;
    int fd;
    char *pid_str;

    pid_str = ft_itoa(getpid(), head);
    if (!pid_str)
        return (NULL);
    file = ft_strjoin("/tmp/heredoc_", pid_str, head);
    if (!file)
        return (NULL);
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (NULL);
    close(fd);
    return (file);
}

char *heredoc(char *delimiter, t_mini *mini, t_garbege **head)
{
    pid_t pid;
    char *filename;
    int fd;
    char *line;
    int status;

    filename = get_temp_file(head);
    if (!filename || !delimiter)
        return (NULL);
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (NULL);
    pid = fork();
    if (pid == -1)
        return (close(fd), NULL);
    signal(SIGINT, SIG_IGN);
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
    waitpid(pid, &status, 0);
    setup_parent_signals();
    mini->exit = WEXITSTATUS(status);
    return (filename);
}
