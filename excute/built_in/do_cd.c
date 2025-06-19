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
	char	new_pwd[MAX_PATH];
	char	*tmp;
	char	*pwd;

	if (!getcwd(new_pwd, sizeof(new_pwd)))
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

void	do_cd(char **cmd, t_mini *mini, t_garbege **head)
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
		mini->exit = 1;
		return ;
	}
	if (!getcwd(NULL, 0))
	{
		ft_putstr_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories:", 2);
		ft_putstr_fd(" No such file or directory\n", 2);
	}
	update_env(&mini->env, "OLDPWD", cwd, head);
	update_env(&mini->export_env, "OLDPWD", cwd, head);
	update_pwd(mini, cwd, target, head);
}
