/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 20:15:30 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/17 20:59:45 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_pipes(t_command	*s_cmd)
{
	t_simple_cmd	*cmd;

	cmd = s_cmd->first_cmd;
	while (cmd)
	{
		if (cmd->next)
		{
			close(cmd->outfile);
			close(cmd->infile);
		}
		cmd = cmd->next;
	}
}
