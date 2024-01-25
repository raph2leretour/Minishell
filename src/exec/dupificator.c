/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupificator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:27:53 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/25 03:39:20 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_redirection(t_simple_cmd *cmd)
{
	if (cmd->here_in != -1)
	{
		if (dup2(cmd->here_in, STDIN_FILENO) < 0)
		{
			return (-1);
		}
	}
	else
	{
		if (dup2(cmd->infile, STDIN_FILENO) < 0)
		{
			return (-1);
		}
	}
	if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
	{
		close_fds(cmd, true);
		return (-1);
	}
	close_fds(cmd, true);
	return (0);
}
