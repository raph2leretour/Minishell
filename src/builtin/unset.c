/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:39:50 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/13 18:28:45 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_env *env, char *tkey)
{
	t_env	*head;
	t_env	*prev;
	t_env	*next;

	if (!env || !tkey)
		return ;
	head = env;
	while (env)
	{
		if (!ft_strncmp(tkey, env->key, ft_strlen(tkey)))
		{
			prev = env->prev;
			next = env->next;
			free(env->key);
			free(env->value);
			free(env);
			if (next)
				prev->next = next;
			else
				prev->next = NULL;
			if (prev)
				next->prev = prev;
			else
				next->prev = NULL;
			env = head;
			return ;
		}
		env = env->next;
	}
	env = head;
}
