/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_true_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:18:13 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/19 16:39:08 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_truc_env(t_env *s_env)
{
	int		i;
	char	**envp;

	i = 0;
	while (s_env && s_env->key)
	{
		if (s_env->value)
		{
			envp[i] = ft_strjoin(s_env->key, "=");
			envp[i] = ft_strjoin(envp[i], s_env->value);
		}
		else
		{
			envp[i] = ft_strdup(s_env->key);
		}
		i++;
		s_env = s_env->next;
	}
	return (envp);
}
