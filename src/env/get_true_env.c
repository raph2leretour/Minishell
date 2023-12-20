/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_true_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:18:13 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/20 19:42:48 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_env(t_env *s_env)
{
	int		i;
	char	**c_env;
	t_env	*head;

	head = s_env;
	i = 0;
	while (s_env)
	{
		i++;
		s_env = s_env->next;
	}
	s_env = head;
	c_env = malloc(sizeof(char *) * (i + 1));
	return c_env;
}

char	**get_true_env(t_env *s_env)
{
	int		i;
	char	**c_env;
	t_env	*head;

	head = s_env;
	c_env = malloc_env(s_env);
	i = 0;
	while (s_env && s_env->key)
	{
		if (s_env->value)
		{
			c_env[i] = ft_strjoin(s_env->key, "=");
			c_env[i] = ft_strjoin(c_env[i], s_env->value);
		}
		else
		{
			c_env[i] = ft_strdup(s_env->key);
		}
		i++;
		s_env = s_env->next;
	}
	c_env[i] = NULL;
	s_env = head;
	return (c_env);
}
