/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:39:50 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/17 21:00:29 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char *name, t_env *env)
{
	t_env	*head;
	t_env	*next;
	t_env	*prev;

	head = env;
	while (env && env->next && \
		ft_strncmp(name, env->next->value, ft_strlen(name)))
		env = env->next;
	prev = env;
	env = env->next;
	next = env->next;
	free(env->value);
	free(env);
	env = prev;
	env->next = next;
	env = head;
}
