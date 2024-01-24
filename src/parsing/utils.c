/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:45:12 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/23 18:46:06 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

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
