/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:20:07 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/20 19:38:54 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_error(char *value)
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

int	is_non_valid(char *value)
{
	int	i;

	if (ft_isdigit(value[0]))
		return (format_error(value), 1);
	i = 0;
	while (value[i] && value[i] != '=')
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (format_error(value), 1);
		i++;
	}
	while (value[i])
	{
		if (!ft_isprint(value[i]))
			return (format_error(value), 1);
		i++;
	}
	return (0);
}

void	no_arg(t_env *env)
{
	t_env	*head;

	head = env;
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd("export ", 1);
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			ft_putstr_fd("export ", 1);
			ft_putstr_fd(env->key, 1);
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
	env = head;
}

void	ft_export(t_command *s_cmd, t_token *token)
{
	if (token && token->str)
	{
		if (is_non_valid(token->str))
			return ;
		get_env_vars(s_cmd, &token->str);
		// while (env && env->next)
		// 	env = env->next;
		// env->next = malloc(sizeof(t_env *));
		// env = env->next;
		// env->value = malloc(sizeof(char) * (ft_strlen(value) + 1));
		// ft_strlcpy(env->value, value, ft_strlen(value) + 1);
		// env->e = true;
		// env->next = NULL;
	}
	else
	{
		no_arg(s_cmd->lst_env);
	}
}
