/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:41:30 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/15 18:14:09 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	create_pipe(t_command *s_cmd)
{
	int				pip[2];
	t_simple_cmd	*head;
	t_simple_cmd	*cmd;

	cmd = s_cmd->first_cmd;
	head = cmd;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pip))
			{
				perror("Pipe:");
				return (-1);
			}
			cmd->outfile = pip[1];
			cmd->infile = pip[0];
		}
		cmd = cmd->next;
	}
	cmd = head;
}
