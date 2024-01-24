/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupificator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:27:53 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/24 11:15:38 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_redirection(t_simple_cmd *cmd)
{
	cmd->in = dup(STDIN_FILENO);
	cmd->out = dup(STDOUT_FILENO);
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
	close(cmd->infile);
	return (0);
}

int	dupificator(t_simple_cmd *cmd)
{
	if (cmd && cmd->first_token && is_builtin(cmd->first_token->str)
		&& (is_any_redirection(cmd) || cmd->here_in != -1))
		return (dup_redirection(cmd));
	else
	{
		if (cmd->here_in != -1)
		{
			if (dup2(cmd->here_in, STDIN_FILENO) < 0)
				return (-1);
		}
		else
		{
			if (dup2(cmd->infile, STDIN_FILENO) < 0)
				return (-1);
		}
		if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
		{
			close_fds(cmd, true);
			return (-1);
		}
	}
	close_fds(cmd, true);
	return (0);
}
