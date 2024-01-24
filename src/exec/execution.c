/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:41:30 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/25 00:27:41 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_many_cmds(t_command *t_cmd, int status)
{
	if (t_cmd && t_cmd->lst_env)
		free_env(t_cmd->lst_env);
	if (t_cmd)
		free_cmd(t_cmd);
	exit(status);
}

int	do_builtin(t_command *t_cmd, t_simple_cmd *cmd, t_token *token, int b)
{
	int	status;

	status = 0;
	if (!ft_strcmp(token->str, "cd"))
		status = cd(t_cmd, token, t_cmd->lst_env);
	else if (!ft_strcmp(token->str, "echo"))
		status = echo(split_cmd(cmd, 1), t_cmd->lst_env);
	else if (!ft_strcmp(token->str, "env"))
		status = ft_env(t_cmd->lst_env);
	else if (!ft_strcmp(token->str, "exit"))
		status = ft_exit(t_cmd, cmd->first_token->next);
	else if (!ft_strcmp(token->str, "export"))
		status = ft_export(t_cmd, cmd->first_token->next);
	else if (!ft_strcmp(token->str, "pwd"))
		status = pwd();
	else if (!ft_strcmp(token->str, "unset"))
		status = unset(t_cmd, token->next);
	redirect_end(cmd);
	if (b)
		is_many_cmds(t_cmd, status);
	return (status);
}

void	free_exit(t_command *t_cmd, char **c_env, char **s_cmd, int exit_status)
{
	redirect_end(t_cmd->first_cmd);
	free_array(c_env);
	free_array(s_cmd);
	free_env(t_cmd->lst_env);
	free_cmd(t_cmd);
	exit(exit_status);
}

void	do_exec(t_command *t_cmd, t_simple_cmd *t_scmd, t_env *s_env)
{
	char	**c_env;
	char	**s_cmd;

	ft_karl(t_scmd->first_token);
	if (!t_scmd->full_path)
	{
		if (!ft_strchr(t_scmd->first_token->str, '/'))
		{
			ft_dprintf(2, "minishell: %s: Command Not Found\n", \
				t_scmd->first_token->str);
			free_exit(t_cmd, NULL, NULL, 127);
		}
		t_scmd->full_path = ft_strdup(t_scmd->first_token->str);
	}
	c_env = get_true_env(s_env);
	s_cmd = split_cmd(t_scmd, 0);
	if (! s_cmd)
	{
		free_exit(t_cmd, c_env, s_cmd, 2);
	}
	execve(t_scmd->full_path, s_cmd, c_env);
	ft_dprintf(2, "%s: %s\n", t_scmd->first_token->str, strerror(errno));
	free_exit(t_cmd, c_env, s_cmd, 126);
}

int	execution(t_command *t_cmd, t_simple_cmd *cmd)
{
	pid_t	pid;

	while (cmd)
	{
		pid = fork();
		if (pid == -1)
		{
			close_fds(t_cmd->first_cmd, true);
			perror("minishell: Fork:");
			return (-1);
		}
		else if (pid == 0)
		{
			restore_signal();
			child_process(t_cmd, cmd);
		}
		ignor_signal();
		close_fds(cmd, false);
		cmd = cmd->next;
	}
	ft_wait(pid);
	return (0);
}
