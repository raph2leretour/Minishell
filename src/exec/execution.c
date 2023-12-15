/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:41:30 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/15 14:03:53 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	execution(t_command *s_cmd)
{
	pid_t			pid;
	t_simple_cmd	cmd;

	cmd = s_cmd->first_cmd;
	while (cmd)
	{
		pid = fork();
		if (pid == 0)
			perror("fork:");
	}
}
