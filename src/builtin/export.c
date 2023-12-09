/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:20:07 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/09 18:50:32 by rtissera         ###   ########.fr       */
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
		return (inid(value), 1);
	i = 0;
	while (value[i] && value[i] != '=')
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (inid(value), 1);
		i++;
	}
	while (value[i])
	{
		if (!ft_isprint(value[i]))
			return (inid(value), 1);
		i++;
	}
	return (0);
}

void	ft_export(char *value, t_env *env)
{
	char	**print;
	t_env	*head;

	if (value)
	{
		if (is_valid(value))
			return ;
		head = env;
		while (env && env->next)
			env = env->next;
		env->next = malloc(sizeof(t_env *));
		env = env->next;
		env->value = malloc(sizeof(char) * (ft_strlen(value) + 1));
		ft_strlcpy(env->value, value, ft_strlen(value) + 1);
		env->e = true;
		env->next = NULL;
	}
	else
	{
		head = env;
		while (env)
		{
			print = ft_split(env->value, '=');
			printf("declare -x %s=\"%s\"\n", print[0], print[1]);
			env = env->next;
		}
	}
	env = head;
}
