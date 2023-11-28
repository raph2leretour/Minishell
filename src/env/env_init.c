/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:00:55 by rtissera          #+#    #+#             */
/*   Updated: 2023/11/28 18:40:03 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_init(char **env)
{
	int		i;
	t_env	*env_s;
	t_env	*head;

	i = 0;
	env_s = malloc(sizeof(t_env *));
	env_s->value = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
	ft_strlcpy(env_s->value, env[i], ft_strlen(env[i]));
	env_s->e = false;
	head = env_s;
	while (env[i])
	{
		env_s->next = malloc(sizeof(t_env *));
		env_s = env_s->next;
		env_s->value = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		ft_strlcpy(env_s->value, env[i], ft_strlen(env[i]));
		env_s->e = false;
		i++;
	}
	env_s->next = NULL;
	return (head);
}
