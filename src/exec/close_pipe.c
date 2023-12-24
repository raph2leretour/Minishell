/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:29:11 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/24 18:32:09 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_simple_cmd *cmd)
{
	while (cmd)
	{
		close(cmd->infile);
		close(cmd->outfile);
		cmd = cmd->next;
	}
}
