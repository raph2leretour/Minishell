/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:07:35 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/24 11:12:30 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_simple_cmd *cmd, bool do_next)
{
	while (cmd)
	{
		if (cmd->here_in != -1)
		{
			if (cmd->here_in && cmd->here_in > 2)
				close(cmd->here_in);
		}
		else
		{
			if (cmd->infile && cmd->infile > 2)
				close(cmd->infile);
		}
		if (cmd->outfile && cmd->outfile > 2)
			close(cmd->outfile);
		if (do_next)
			cmd = cmd->next;
		else
			break ;
	}
}
