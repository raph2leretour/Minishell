/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:55:39 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/17 18:14:12 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	ft_env(t_env *env)
{
	while (env && env->value)
	{
		if (!env->e)
			printf("%s\n", env->value);
		env = env->next;
	}
}
