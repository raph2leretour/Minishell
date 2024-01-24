/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:39:50 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/24 08:36:19 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*free_solo_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
	return (NULL);
}

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

void	freetor(t_command *t_cmd, t_env **head)
{
	t_env	*prev;
	t_env	*next;

	prev = t_cmd->lst_env->prev;
	next = t_cmd->lst_env->next;
	if (t_cmd->lst_env == *head && !t_cmd->lst_env->next)
		*head = NULL;
	else if (t_cmd->lst_env == *head)
		*head = next;
	free(t_cmd->lst_env->key);
	free(t_cmd->lst_env->value);
	free(t_cmd->lst_env);
	unsetor(prev, next);
}

int	unset(t_command *t_cmd, t_token *token)
{
	t_env	*head;

	if (!t_cmd->lst_env)
		return (1);
	head = t_cmd->lst_env;
	while (token)
	{
		while (t_cmd->lst_env)
		{
			if (!ft_strcmp(token->str, t_cmd->lst_env->key))
			{
				freetor(t_cmd, &head);
				break ;
			}
			t_cmd->lst_env = t_cmd->lst_env->next;
		}
		t_cmd->lst_env = head;
		token = token->next;
	}
	return (0);
}
