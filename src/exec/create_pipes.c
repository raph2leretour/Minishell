/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:41:30 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/24 11:13:22 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(t_command *t_cmd)
{
	int				pipefd[2];
	t_simple_cmd	*cmd;

	cmd = t_cmd->first_cmd;
	while (cmd)
	{
		if (cmd->next)
		{
			if (!is_any_redirection(cmd))
			{
				if (pipe(pipefd))
				{
					perror("Pipe:");
					close_fds(t_cmd->first_cmd, true);
					return (-1);
				}
				cmd->outfile = pipefd[1];
				cmd->next->infile = pipefd[0];
			}
		}
		cmd = cmd->next;
	}
	return (0);
}
