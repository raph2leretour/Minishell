/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:20:07 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/06 13:34:06 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inid(char *value)
{
	char	*errc;
	char	*errc2;

	errc = ft_strdup("bash: export: `");
	ft_strlcat(errc, value, ft_strlen(errc) + ft_strlen(value));
	errc2 = ft_strdup("': not a valid identifier");
	ft_strlcat(errc, errc2, ft_strlen(errc) + ft_strlen(errc2));
	free(errc2);
	ft_error(errc, -1);
	free(errc);
}

int	is_valid(char *value)
{
	int	i;

	if (ft_isdigit(value[0]))
		return (inid(value), 0);
	i = 0;
	while (value[i] && value[i] != '=')
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (inid(value), 0);
		i++;
	}
	while (value[i])
	{
		if (!ft_isprint(value[i]))
			return (inid(value), 0);
		i++;
	}
	return (i);
}

void	ft_export(char *value, t_env *env)
{
	int		i;
	t_env	*head;

	if (value)
	{
		i = is_valid(value);
		if (i == 0)
			return ;
		head = env;
		while (env && env->next)
			env = env->next;
		env->next = malloc(sizeof(t_env *));
		env = env->next;
		i = 0;
		while (value[i] && value[i] != '=')
			i++;
		env->name = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(env->name, value, i + 1);
		env->value = malloc(sizeof(char) * (ft_strlen(value) - i));
		ft_strlcpy(env->value, value + i + 1, ft_strlen(value) - i + 1);
		env->e = true;
	}
	else
	{
		head = env;
		while (env)
		{
			if (env->e)
				printf("declare -x %s=\"%s\"", env->name, env->value);
			env = env->next;
		}
	}
	env = head;
}
