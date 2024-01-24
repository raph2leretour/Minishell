/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:26:22 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/24 15:31:08 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *s, t_env *env)
{
	t_env	*head;

	head = env;
	while (env)
	{
		if (!ft_strcmp(env->key, s))
			return (env->value);
		env = env->next;
	}
	env = head;
	return (NULL);
}

bool	is_env(char *s, t_env *env)
{
	t_env	*head;

	head = env;
	while (env)
	{
		if (!ft_strcmp(env->key, s))
			return (true);
		env = env->next;
	}
	env = head;
	return (false);
}
