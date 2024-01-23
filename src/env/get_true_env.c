/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_true_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:18:13 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/23 13:03:45 by rtissera         ###   ########.fr       */
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
	if (!c_env)
		c_env = NULL;
	return (c_env);
}

char	*maillon_env(t_env *s_env)
{
	char	*tmp;
	char	*ret;

	if (s_env->value)
	{
		tmp = ft_strjoin(s_env->key, "=");
		ret = ft_strjoin(tmp, s_env->value);
		free(tmp);
	}
	else
	{
		ret = ft_strdup(s_env->key);
	}
	return (ret);
}

char	**get_true_env(t_env *s_env)
{
	int		i;
	char	**c_env;
	t_env	*head;

	head = s_env;
	c_env = malloc_env(s_env);
	if (!c_env)
		return (ft_dprintf(2, "Error: Cannot Access Env\n"), NULL);
	i = 0;
	while (s_env && s_env->key)
	{
		c_env[i] = maillon_env(s_env);
		if (!c_env[i])
		{
			ft_dprintf(2, "Error: Cannot Access Env\n");
			freeror(c_env);
			s_env = head;
			return (NULL);
		}
		i++;
		s_env = s_env->next;
	}
	c_env[i] = NULL;
	s_env = head;
	return (c_env);
}
