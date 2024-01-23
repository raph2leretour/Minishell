/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:15:28 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/23 19:49:54 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_env *env)
{
	char	*key;
	char	*v_pwd;
	t_env	*t_pwd;

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
	else
	{
		t_pwd = init_env_var(key, v_pwd);
		add_env_var(&env, t_pwd);
	}
}

void	set_oldpwd(t_env *env, char *v_oldpwd)
{
	char	*key;
	t_env	*t_oldpwd;

	if (v_oldpwd && v_oldpwd[0])
	{
		key = ft_strdup("OLDPWD");
		if (ft_getenv(key, env))
		{
			ft_reset(env, key, v_oldpwd);
			free(key);
			free(v_oldpwd);
		}
		else
		{
			t_oldpwd = init_env_var(key, v_oldpwd);
			add_env_var(&env, t_oldpwd);
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
	set_pwd(env);
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
	set_pwd(env);
	return (0);
}

int	cd(t_command *cmd, t_token *token, t_env *env)
{
	char	*path;
	char	*oldpwd;

	if (is_pipe(cmd))
		return (1);
	path = NULL;
	if (token->next && token->next->str)
		path = token->next->str;
	oldpwd = getcwd(NULL, 0);
	if (!path)
	{
		if (cd_no_path(env) < 0)
			return (1);
	}
	else if (!ft_strcmp(path, "-"))
	{
		if (cd_less_symbol(env) < 0)
			return (1);
	}
	else
	{
		cd_arg(env, path, oldpwd);
	}
	return (0);
}
