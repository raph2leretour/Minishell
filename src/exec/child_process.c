/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:00:10 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/25 06:06:43 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_command *t_cmd, t_simple_cmd *cmd)
{
	if (dup_redirection(cmd) < 0)
	{
		close_fds(cmd, true);
		if (t_cmd)
			free_env(t_cmd->lst_env);
		free_cmd(t_cmd);
		exit(1);
	}
	if (is_builtin(cmd->first_token->str) || !ft_strcmp(cmd->first_token->str, \
		">") || !ft_strcmp(cmd->first_token->str, ">>") || \
		!ft_strcmp(cmd->first_token->str, "<<"))
		do_builtin(t_cmd, cmd, cmd->first_token, 1);
	else
		do_exec(t_cmd, cmd, t_cmd->lst_env);
}
