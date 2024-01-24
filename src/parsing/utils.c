/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:45:12 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/25 00:38:36 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_heredoc(t_simple_cmd *simple_cmd)
{
	t_token	*token;

	token = simple_cmd->first_token;
	while (token)
	{
		if (token->type == REDIRECTION
			&& !ft_strcmp(token->str, "<<"))
			return (0);
		token = token->next;
	}
	return (1);
}

int	check_exec(t_simple_cmd *simple_cmd)
{
	t_token	*token;

	token = simple_cmd->first_token;
	while (token)
	{
		if (token->type == COMMAND && !ft_strcmp(token->str, "./"))
			return (1);
		token = token->next;
	}
	return (0);
}

int	set_option_type(t_simple_cmd *simple_cmd)
{
	t_token	*token;

	while (simple_cmd)
	{
		if (simple_cmd->full_path != NULL)
		{
			token = simple_cmd->first_token;
			while (token)
			{
				if (token->str[0] == '-')
					token->type = OPTION;
				token = token->next;
			}
		}
		simple_cmd = simple_cmd->next;
	}
	return (1);
}

int	is_absolute_path(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			j++;
		i++;
	}
	if (j == 1 || j == 0)
		return (0);
	if (access(cmd, F_OK) == 0)
		return (1);
	return (0);
}

int	cmd_contains_builtin(t_simple_cmd *simple_cmd)
{
	t_token	*token;

	token = simple_cmd->first_token;
	while (token)
	{
		if (is_builtin(token->str))
		{
			token->type = COMMAND;
			return (1);
		}
		token = token->next;
	}
	return (0);
}
