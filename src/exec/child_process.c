/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:00:10 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/29 17:25:20 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_command *t_cmd, t_simple_cmd *cmd)
{
	dupificator(cmd);
	if (is_builtin(cmd->first_token->str))
		do_builtin(t_cmd, cmd, cmd->first_token, 1);
	else
		do_exec(cmd, t_cmd->lst_env);
}
