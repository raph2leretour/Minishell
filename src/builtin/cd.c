/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:15:28 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/19 17:36:15 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_env *env)
{
	char	*key;
	char	*v_pwd;

	key = ft_strdup("PWD");
	v_pwd = getcwd(NULL, 0);
	if (!v_pwd)
	{
		perror("minishell: cd");
		return ;
	}
	if (ft_getenv(key, env))
	{
		ft_reset(env, key, v_pwd);
		free(key);
		free(v_pwd);
	}
}

void	set_oldpwd(t_env *env, char *v_oldpwd)
{
	char	*key;

	if (v_oldpwd && v_oldpwd[0])
	{
		key = ft_strdup("OLDPWD");
		if (ft_getenv(key, env))
		{
			ft_reset(env, key, v_oldpwd);
			free(key);
			free(v_oldpwd);
		}
	}
	set_pwd(env);
}

int	cd_less_symbol(t_env *env)
{
	char	*oldpwd;

	oldpwd = ft_getenv("OLDPWD", env);
	if (oldpwd)
	{
		if (chdir(oldpwd) < 0)
		{
			perror("minishell: cd");
			return (-1);
		}
	}
	else
	{
		ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
		return (-1);
	}
	return (0);
}

int	cd_no_path(t_env *env)
{
	char	*home;

	home = ft_getenv("HOME", env);
	if (home)
	{
		if (chdir(home) < 0)
		{
			perror("minishell: cd");
			return (-1);
		}
	}
	else
	{
		ft_dprintf(2, "minishell: cd: HOME not set\n");
		return (-1);
	}
	return (0);
}

void	cd(t_token *token, t_env *env)
{
	char	*tmp;
	char	*path;
	char	*oldpwd;

	path = NULL;
	tmp = NULL;
	if (token->next && token->next->str)
		path = token->next->str;
	oldpwd = getcwd(NULL, 0);
	if (!path)
	{
		if (cd_no_path(env) < 0)
			return ;
	}
	else if (!ft_strcmp(path, "-"))
	{
		if (cd_less_symbol(env) < 0)
			return ;
	}
	else
	{
		if (!ft_strcmp(path, ".."))
			tmp = ft_strjoin(path, "/");
		else
			tmp = ft_strdup(path);
		if (chdir(tmp) < 0)
		{
			perror("minishell: cd");
			free(tmp);
			if (oldpwd)
				free(oldpwd);
			return ;
		}
		free(tmp);
	}
	set_oldpwd(env, oldpwd);
}
