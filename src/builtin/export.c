/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:20:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/21 11:37:57 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_error(char *value)
{
	char	*errc;
	char	*errc2;

	errc = ft_strdup("minishell: export: `");
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
		{
			return (format_error(value), 1);
		}
		i++;
	}
	while (value[i])
	{
		if (!ft_isprint(value[i]))
		{
			return (format_error(value), 1);
		}
		i++;
	}
	return (0);
}

void	no_arg(t_env *env)
{
	t_env	*head;

	head = env;
	while (env && env->key)
	{
		if (env->value && env->value[0])
		{
			ft_dprintf(1, "export %s=\"%s\"\n", env->key, env->value);
		}
		else
		{
			ft_dprintf(1, "export %s\n", env->key);
		}
		env = env->next;
	}
	env = head;
}

void	ft_reset(t_env *env, char *key, char *value)
{
	t_env	*head;

	if (value && value[0])
	{
		head = env;
		while (env)
		{
			if (!ft_strcmp(env->key, key))
			{
				free(env->value);
				env->value = ft_substr(value, 0, ft_strlen(value));
				env = head;
				return ;
			}
			env = env->next;
		}
		env = head;
	}
}

int	ft_export(t_command *s_cmd, t_token *token)
{
	char	*key;
	char	*value;
	t_env	*new_env_var;

	if (token && token->str)
	{
		if (is_non_valid(token->str))
			return (1);
		key = get_key(token->str);
		value = get_value(token->str);
		if (ft_getenv(key, s_cmd->lst_env))
		{
			ft_reset(s_cmd->lst_env, key, value);
			free(key);
			free(value);
		}
		else
		{
			new_env_var = init_env_var(key, value);
			add_env_var(&s_cmd->lst_env, new_env_var);
		}
	}
	else
		no_arg(s_cmd->lst_env);
	return (0);
}
