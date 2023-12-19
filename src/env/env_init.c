/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:00:55 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/19 17:23:47 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
t_env	*env_init(char **env)
{
	int		i;
	t_env	*env_s;
	t_env	*head;

	i = 0;
	env_s = malloc(sizeof(t_env *));
	env_s->value = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
	ft_strlcpy(env_s->value, env[i], ft_strlen(env[i]));
	env_s->e = false;
	head = env_s;
	while (env[i])
	{
		env_s->next = malloc(sizeof(t_env *));
		env_s = env_s->next;
		env_s->value = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		ft_strlcpy(env_s->value, env[i], ft_strlen(env[i]));
		env_s->e = false;
		i++;
	}
	env_s->next = NULL;
	return (head);
}
 */
t_env	*env_init(char **env)
{
	int		i;
	int		key_size;
	int		val_size;
	t_env	*s_env;
	t_env	*head;

	i = 0;
	while (env[i])
	{
		s_env = malloc(sizeof(t_env *));
		key_size = 0;
		while (env[i][key_size] != '=')
			key_size++;
		s_env->key = malloc(sizeof(char) * (key_size + 1));
		ft_strlcpy(s_env->key, env[i], key_size);
		val_size = ft_strlen(ft_strchr(env[i], '='));
		s_env->value = malloc(sizeof(char) * val_size);
		ft_strlcpy(s_env->value, ft_strchr(env[i], '=') + 1, val_size);
		if (i = 0)
			head = s_env;
		i++;
		s_env = s_env->next;
	}
	s_env = NULL;
	return (head);
}
