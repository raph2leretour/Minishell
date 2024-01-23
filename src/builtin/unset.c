/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:39:50 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/23 17:22:21 by rtissera         ###   ########.fr       */
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

void	freetor(t_env *env, t_env *head)
{
	t_env	*prev;
	t_env	*next;

	prev = env->prev;
	next = env->next;
	if (env == head)
		head = next;
	free(env->key);
	free(env->value);
	free(env);
	unsetor(prev, next);
}

int	unset(t_env *env, t_token *token)
{
	t_env	*head;

	if (!env)
		return (1);
	head = env;
	while (token)
	{
		while (env)
		{
			if (!ft_strcmp(token->str, env->key))
			{
				freetor(env, head);
				break ;
			}
			env = env->next;
		}
		env = head;
		token = token->next;
	}
	return (0);
}
