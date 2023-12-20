/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:41:30 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/19 13:28:16 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(t_command *t_cmd)
{
	int				pip[2];
	t_simple_cmd	*cmd;

	cmd = t_cmd->first_cmd;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pip))
			{
				perror("Pipe:");
				clear_pipes(t_cmd);
				return (-1);
			}
			cmd->outfile = pip[1];
			cmd->infile = pip[0];
		}
		cmd = cmd->next;
	}
	return (0);
}
