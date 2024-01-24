/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_executables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:10:48 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/23 18:59:31 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	set_executable(t_token *token)
{
	if (access(token->str + 2, F_OK) == 0)
		token->type = COMMAND;
}

int	check_executables(t_command *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (!ft_strncmp(token->str, "./", 2))
			set_executable(token);
		token = token->next;
	}
	return (1);
}
