/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:15:28 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/23 11:56:37 by rtissera         ###   ########.fr       */
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

void	set_oldpwd(t_env *env, char *value)
{
	char	*key;
	char	*ispwd;
	t_env	*oldpwd;
	t_env	*head;

	ispwd = ft_getenv("OLDPWD", env);
	if (!ispwd)
	{
		key = ft_strdup("OLDPWD");
		oldpwd = init_env_var(key, value);
		add_env_var(&env, oldpwd);
	}
	else
	{
		head = env;
		while (env && ft_strncmp(env->key, "OLDPWD", 6))
			env = env->next;
		free(env->value);
		env->value = ft_strdup(value);
		env = head;
	}
}

void	cd(char *path, t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!path)
	{
		if (chdir(ft_getenv("HOME", env)))
			return (printf("bash: cd: HOME not set\n"), (void)pwd);
	}
	else if (!ft_strncmp(path, "-", 1))
	{
		if (chdir(ft_getenv("OLDPWD", env)))
			printf("bash: cd: OLDPWD not set\n");
		else
			return (printf("%s\n", getenv("OLDPWD")), (void)pwd);
	}
	else if (chdir(path))
		return (perror("bash: cd"), (void)pwd);
	set_oldpwd(env, pwd);
}
