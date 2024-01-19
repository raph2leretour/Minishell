/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupificator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:27:53 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/17 14:42:45 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_redirection(t_simple_cmd *cmd)
{
	cmd->in = dup(STDIN_FILENO);
	cmd->out = dup(STDOUT_FILENO);
	if (dup2(cmd->infile, STDIN_FILENO) < 0)
	{
		perror("minishell: in");
		return (-1);
	}
	if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
	{
		close_fds(cmd);
		perror("minishell: out");
		return (-1);
	}
	close(cmd->infile);
	return (0);
}

int	dupificator(t_simple_cmd *cmd)
{
	if (cmd && cmd->first_token && is_builtin(cmd->first_token->str)
		&& is_any_redirection(cmd))
		return (dup_redirection(cmd));
	else
	{
		if (dup2(cmd->infile, STDIN_FILENO) < 0)
		{
			perror("minishell: in");
			return (-1);
		}
		if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
		{
			close_fds(cmd);
			perror("minishell: out");
			return (-1);
		}
	}
	close_fds(cmd);
	return (0);
}
