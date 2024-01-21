/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:55:39 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/21 11:46:09 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->key && env->key[0] && env->value && env->value[0])
		{
			ft_dprintf(1, "%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
	return (0);
}
