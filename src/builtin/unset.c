/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:39:50 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/20 20:14:44 by rtissera         ###   ########.fr       */
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
			prev->next = next;
			env = head;
			return ;
		}
		env = env->next;
	}
	env = head;
}
