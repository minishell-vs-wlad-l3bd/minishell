/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:36:25 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/30 11:38:48 by aayad            ###   ########.fr       */
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

// void cleanup_heredoc(t_mini *mini, char *filename, int fd)
// {
//     if (filename)
//         unlink(filename);
//     if (fd != -1)
//         close(fd);
//     signal(SIGINT, handler);
// }

char *heredoc(t_mini *mini, char *delimiter)
{
    char *filename = get_temp_file();
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char *line;

    if (!filename || fd == -1 || !delimiter)
        return NULL;

    // signal(SIGINT, SIG_DFL);
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (!ft_strcmp(line, delimiter))
            break;
        ft_putendl_fd(line, fd);
    }
    close(fd);
    signal(SIGINT, handler);
    return filename;
}
