/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupificator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:27:53 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/29 15:47:40 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dupificator(t_simple_cmd *cmd)
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
	close_fds(cmd);
	return (0);
}
