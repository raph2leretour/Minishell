/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:35:17 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/26 14:53:01 by rtissera         ###   ########.fr       */
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
		do_builtin(t_cmd, t_cmd->first_cmd, t_cmd->first_token);
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
		// close_fds(t_cmd->first_cmd);
	}
}
/*
--> ls -la file1 blablabla

execve(arg1, arg2);
char *arg1 = "/usr/bin/ls";
char **arg2;
arg2[0] = "ls";
arg2[1] = "-la";
arg2[2] = "file1";
arg2[3] = NULL;

type command --> premier mot de ta liste chainee type 0
ls

type option --> -la type 1

type argument --> file1 type 2

while (cmd)
if (cmd->type <= 2)
	cmd->tokken->str
	cmd = cmd->next;
 */
