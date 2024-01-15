/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:15:28 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/15 15:39:46 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *s, t_env *env)
{
	t_env	*head;

	head = env;
	while (env)
	{
		if (!ft_strncmp(env->key, s, ft_strlen(s)))
			return (env->value);
		env = env->next;
	}
	env = head;
	return (NULL);
}

void	set_oldpwd(t_env *env, char *v_oldpwd)
{
	char	*key;
	t_env	*t_oldpwd;

	key = ft_strdup("OLDPWD");
	if (!ft_getenv("OLDPWD", env))
	{
		t_oldpwd = init_env_var(key, v_oldpwd);
		add_env_var(&env, t_oldpwd);
	}
	else
	{
		ft_reset(env, key, v_oldpwd);
		free(key);
		free(v_oldpwd);
	}
}

int	cd_less_symbol(t_env *env)
{
	char	*oldpwd;

	oldpwd = ft_getenv("OLDPWD", env);
	if (oldpwd)
	{
		if (chdir(oldpwd) < 0)
		{
			perror("bash: cd");
			return (-1);
		}
	}
	else
	{
		ft_dprintf(2, "bash: cd: OLDPWD not set\n");
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
			perror("bash: cd");
			return (-1);
		}
	}
	else
	{
		ft_dprintf(2, "bash: cd: HOME not set\n");
		return (-1);
	}
	return (0);
}

void	cd(char *path, t_env *env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!path)
	{
		if (cd_no_path(env) < 0)
			return ;
	}
	else if (!ft_strncmp(path, "-", 1))
	{
		if (cd_less_symbol(env) < 0)
			return ;
	}
	else if (chdir(path) < 0)
	{
		perror("bash: cd");
		if (oldpwd)
			free(oldpwd);
		return ;
	}
	set_oldpwd(env, oldpwd);
}
