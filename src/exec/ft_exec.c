/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:35:17 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/29 17:25:24 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_command *t_cmd)
{
	int	status;
	int	return_value;

	if (!t_cmd || !t_cmd->first_cmd)
		return ;
	if (!t_cmd->first_cmd->full_path && !t_cmd->first_cmd->next)
	{
		if (dupificator(t_cmd->first_cmd))
			return ;
		do_builtin(t_cmd, t_cmd->first_cmd, t_cmd->first_token, 0);
	}
	else
	{
		if (create_pipe(t_cmd))
			return ;
		execution(t_cmd, t_cmd->first_cmd);
		while (waitpid(-1, &status, 0) == -1)
		{
			if (WIFEXITED(status))
			{
				return_value = status;
			}
		}
	}
}
