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

static void	update_pwd(t_mini *mini, char *cwd, char *target)
{
	char	new_pwd[MAX_PATH];
	char	*tmp;
	char	*pwd;

	if (!getcwd(new_pwd, sizeof(new_pwd)))
	{
		tmp = ft_strjoin(cwd, "/");
		pwd = ft_strjoin(tmp, target);
		update_env(&mini->env, "PWD", pwd);
		update_env(&mini->export_env, "PWD", pwd);
	}
	else
	{
		update_env(&mini->env, "PWD", new_pwd);
		update_env(&mini->export_env, "PWD", new_pwd);
	}
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
			g_exit_status = 1;
		}
	}
	else
		target = cmd[1];
	return (target);
}

void	do_cd(char **cmd, t_mini *mini)
{
	char	cwd[MAX_PATH];
	char	*target;

	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, get_env_value(mini, "PWD"), MAX_PATH);
	target = get_cd_target(cmd, mini);
	if (!target)
		return ;
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return ;
	}
	update_env(&mini->env, "OLDPWD", cwd);
	update_env(&mini->export_env, "OLDPWD", cwd);
	update_pwd(mini, cwd, target);
}
