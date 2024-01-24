/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:34:29 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 15:27:20 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env_var(char *key, char *value)
{
	t_env	*new_env_var;

	new_env_var = (t_env *)malloc(sizeof(t_env));
	if (!new_env_var)
		return (NULL);
	new_env_var->key = key;
	new_env_var->value = value;
	new_env_var->prev = NULL;
	new_env_var->next = NULL;
	return (new_env_var);
}

char	*get_key(char *env_var)
{
	int		i;
	char	*key;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	key = ft_substr(env_var, 0, i);
	return (key);
}

char	*get_value(char *env_var)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	if (env_var[i])
		i++;
	len = i;
	while (env_var[len])
		len++;
	if (env_var[i - 1] == '=')
		value = ft_substr(env_var, i, len);
	else
		value = NULL;
	return (value);
}

t_env	*get_env_vars(char **envp)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*new_env_var;
	t_env	*env_list;

	i = 0;
	env_list = NULL;
	if (envp)
	{
		while (envp[i])
		{
			key = get_key(envp[i]);
			value = get_value(envp[i]);
			new_env_var = init_env_var(key, value);
			add_env_var(&env_list, new_env_var);
			i++;
		}
	}
	return (env_list);
}
