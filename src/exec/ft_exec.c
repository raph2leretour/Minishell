/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:35:17 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/24 23:25:40 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_command *t_cmd)
{
	if (!t_cmd || !t_cmd->first_cmd)
		return ;
	if (!t_cmd->first_cmd->full_path && !t_cmd->first_cmd->next
		&& is_builtin(t_cmd->first_token->str))
	{
		if (dup_redirection(t_cmd->first_cmd) < 0)
		{
			g_status = (1);
			return ;
		}
		g_status = do_builtin(t_cmd, t_cmd->first_cmd, t_cmd->first_token, 0);
	}
	else
	{
		if (create_pipe(t_cmd))
			return ;
		execution(t_cmd, t_cmd->first_cmd);
	}
}
