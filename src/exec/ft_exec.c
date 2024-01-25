/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:35:17 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/25 05:20:14 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_std_fds(t_command *t_cmd)
{
	t_cmd->first_cmd->in = dup(STDIN_FILENO);
	if (t_cmd->first_cmd->in < 0)
	{
		ft_dprintf(2, \
			"minishell: dup: Fatal Error: Cannot acces STDIN_FILENO\n");
		if (t_cmd)
			free_env(t_cmd->lst_env);
		free_cmd(t_cmd);
		exit(2);
	}
	t_cmd->first_cmd->out = dup(STDOUT_FILENO);
	if (t_cmd->first_cmd->out < 0)
	{
		ft_dprintf(2, \
			"minishell: dup: Fatal Error: Cannot acces STDOUT_FILENO\n");
		close(t_cmd->first_cmd->in);
		if (t_cmd)
			free_env(t_cmd->lst_env);
		free_cmd(t_cmd);
		exit(2);
	}
}

void	restore_std_fds(t_command *t_cmd)
{
	if (dup2(t_cmd->first_cmd->in, STDIN_FILENO) < 0)
	{
		ft_dprintf(2, \
			"minishell: dup: Fatal Error: Cannot restore STDIN_FILENO\n");
		close(t_cmd->first_cmd->in);
		close(t_cmd->first_cmd->out);
		if (t_cmd)
			free_env(t_cmd->lst_env);
		free_cmd(t_cmd);
		exit(2);
	}
	if (dup2(t_cmd->first_cmd->out, STDOUT_FILENO) < 0)
	{
		ft_dprintf(2, \
			"minishell: dup: Fatal Error: Cannot restore STDOUT_FILENO\n");
		close(t_cmd->first_cmd->in);
		close(t_cmd->first_cmd->out);
		if (t_cmd)
			free_env(t_cmd->lst_env);
		free_cmd(t_cmd);
		exit(2);
	}
	close(t_cmd->first_cmd->in);
	close(t_cmd->first_cmd->out);
}

void	ft_exec(t_command *t_cmd)
{
	if (!t_cmd || !t_cmd->first_cmd)
		return ;
	if (!t_cmd->first_cmd->full_path && !t_cmd->first_cmd->next
		&& is_builtin(t_cmd->first_token->str))
	{
		save_std_fds(t_cmd);
		if (dup_redirection(t_cmd->first_cmd) < 0)
		{
			close_fds(t_cmd->first_cmd, true);
			restore_std_fds(t_cmd);
			g_status = (1);
			return ;
		}
		g_status = do_builtin(t_cmd, t_cmd->first_cmd, t_cmd->first_token, 0);
		restore_std_fds(t_cmd);
	}
	else
	{
		if (create_pipe(t_cmd))
			return ;
		execution(t_cmd, t_cmd->first_cmd);
	}
}
