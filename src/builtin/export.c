/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:20:07 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/23 07:39:03 by rtissera         ###   ########.fr       */
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
	char	*key;
	char	*value;
	t_env	*new_env_var;

	if (token && token->str)
	{
		if (is_non_valid(token->str))
			return ;
		key = get_key(token->str);
		value = get_value(token->str);
		new_env_var = init_env_var(key, value);
		add_env_var(&s_cmd->lst_env, new_env_var);
	}
	else
	{
		no_arg(s_cmd->lst_env);
	}
}
