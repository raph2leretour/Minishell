/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:07:35 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/05 17:17:16 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_simple_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->infile && cmd->infile > 2)
			close(cmd->infile);
		if (cmd->outfile && cmd->outfile > 2)
			close(cmd->outfile);
		cmd = cmd->next;
	}
}
