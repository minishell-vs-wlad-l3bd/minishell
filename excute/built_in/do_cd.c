/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:33 by mohidbel          #+#    #+#             */
/*   Updated: 2025/05/22 13:34:33 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

static void	update_pwd(t_mini *mini, char *cwd, char *target, t_garbege **head)
{
	char	*new_pwd;
	char	*tmp;
	char	*pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		tmp = ft_strjoin(cwd, "/", head);
		pwd = ft_strjoin(tmp, target, head);
		update_env(&mini->env, "PWD", pwd, head);
		update_env(&mini->export_env, "PWD", pwd, head);
	}
	else
	{
		update_env(&mini->env, "PWD", new_pwd, head);
		update_env(&mini->export_env, "PWD", new_pwd, head);
	}
	free(new_pwd);
}

static char	*get_cd_target(char **cmd, t_mini *mini)
{
	char	*target;

	if (!cmd[1])
	{
		target = get_env_value(mini, "HOME");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			mini->exit = 1;
		}
	}
	else
		target = cmd[1];
	return (target);
}

static int	prepare_cd(t_mini *mini, char **cwd, char **target, char **cmd)
{
	*cwd = getcwd(NULL, 0);
	if (!*cwd)
	{
		*cwd = get_env_value(mini, "PWD");
		if (!*cwd)
			return (-1);
	}
	*target = get_cd_target(cmd, mini);
	if (!*target)
		return (-1);
	if (chdir(*target) != 0)
	{
		perror("minishell: cd");
		mini->exit = 1;
		return (-1);
	}
	if (*cwd == get_env_value(mini, "PWD"))
		return (0);
	else
		return (1);
}

void	do_cd(char **cmd, t_mini *mini, t_garbege **head)
{
	char	*cwd;
	char	*cwd2;
	char	*target;
	int		free_cwd;
	int		free_cwd2;

	free_cwd = prepare_cd(mini, &cwd, &target, cmd);
	if (free_cwd == -1)
		return (free(cwd));
	cwd2 = getcwd(NULL, 0);
	if (!cwd2)
	{
		free_cwd2 = 0;
		ft_putendl_fd("cd: error retrieving current directory: getcwd: ", 2);
	}
	else
		free_cwd2 = 1;
	update_env(&mini->env, "OLDPWD", cwd, head);
	update_env(&mini->export_env, "OLDPWD", cwd, head);
	update_pwd(mini, cwd, target, head);
	mini->exit = 0;
	if (free_cwd)
		free(cwd);
	if (free_cwd2)
		free(cwd2);
}
