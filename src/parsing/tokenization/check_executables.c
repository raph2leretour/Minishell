/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_executables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:10:48 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 09:56:10 by rtissera         ###   ########.fr       */
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
		if (!ft_strcmp(token->str, "./"))
			set_executable(token);
		token = token->next;
	}
	return (1);
}
