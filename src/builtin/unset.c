/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:39:50 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/19 17:09:23 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unsetor(t_env *prev, t_env *next)
{
	if (prev)
	{
		if (next)
			prev->next = next;
		else
			prev->next = NULL;
	}
	if (next)
	{
		if (prev)
			next->prev = prev;
		else
			next->prev = NULL;
	}
}

void	unset(t_command *cmd, t_env *env, char *tkey)
{
	t_env	*head;
	t_env	*prev;
	t_env	*next;

	if (!env || !tkey)
		return ;
	head = env;
	while (env)
	{
		if (!ft_strcmp(tkey, env->key))
		{
			prev = env->prev;
			next = env->next;
			if (env == head)
				head = next;
			free(env->key);
			free(env->value);
			free(env);
			unsetor(prev, next);
			cmd->lst_env = head;
			return ;
		}
		env = env->next;
	}
	cmd->lst_env = head;
}
