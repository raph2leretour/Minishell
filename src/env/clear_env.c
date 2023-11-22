/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:00:46 by rtissera          #+#    #+#             */
/*   Updated: 2023/11/22 19:02:37 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_env *env)
{
	t_env	*next_env;

	while(env && env->value)
	{
		next_env = env->next;
		free(env->value);
		free(env);
		env = next_env;
	}
	free(env);
}
