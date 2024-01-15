/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:26:22 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/15 17:26:37 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *s, t_env *env)
{
	t_env	*head;

	head = env;
	while (env)
	{
		if (!ft_strncmp(env->key, s, ft_strlen(s)))
			return (env->value);
		env = env->next;
	}
	env = head;
	return (NULL);
}
