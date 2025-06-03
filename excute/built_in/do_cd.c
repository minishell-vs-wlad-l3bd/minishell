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

void	check_valid_folder(char *str, t_mini *mini)
{
	mini->exit = 1;
	if (access(str, F_OK) == -1)
		ft_putendl_fd("minishell: cd: No such file or directory",
			STDERR_FILENO);
	else if (!opendir(str))
	{
		if (access(str, X_OK) == -1)
			ft_putendl_fd("minishell: cd: Permission denied", STDERR_FILENO);
		else
			ft_putendl_fd("minishell: cd: Not a directory", STDERR_FILENO);
	}
}

void	do_cd(char **cmd, t_mini *mini)
{
	char	cwd[MAX_PATH];
	char	*target;
	char	*new_pwd;
	char	*tmp;

	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, get_env_value(mini, "PWD"), MAX_PATH);
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
	if (target)
	{
		if (chdir(target))
			check_valid_folder(target, mini);
		else
		{
			update_env(&mini->env, "OLDPWD", cwd);
			update_env(&mini->export_env, "OLDPWD", cwd);
			new_pwd = getcwd(NULL, 0);
			if (!new_pwd)
			{
				tmp = ft_strjoin(cwd, "/");
				new_pwd = ft_strjoin(tmp, target);
				ft_putendl_fd("cd: error retrieving current directory: getcwd: "
					"cannot access parent directories: No such file or "
					"directory", STDERR_FILENO);
				update_env(&mini->env, "PWD", new_pwd);
				update_env(&mini->export_env, "PWD", new_pwd);
			}
			else
			{
				update_env(&mini->env, "PWD", cwd);
				update_env(&mini->export_env, "PWD", cwd);
			}
		}
	}
}
