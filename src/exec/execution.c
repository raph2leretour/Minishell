/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:41:30 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/18 17:14:21 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(t_command *t_cmd, t_simple_cmd *cmd, t_token *token)
{
	if (ft_strncmp(token->str, "cd", 2))
		return (cd(token->next->str));
	else if (ft_strncmp(token->str, "echo", 4))
		return (echo(split_cmd(cmd)));
	else if (ft_strncmp(token->str, "env", 3))
		return (ft_env(t_cmd->envp));
	else if (ft_strncmp(token->str, "exit", 4))
		return (ft_exit(token->str, t_cmd->envp));
	else if (ft_strncmp(token->str, "export", 6))
		return (ft_export(t_cmd));
	else if (ft_strncmp(token->str, "pwd", 3))
		return (pwd());
	else if (ft_strncmp(token->str, "unset", 5))
		return (unset(t_cmd));
	else
	{
		printf("%s: ", cmd->first_token);
		ft_error("Command Not Found", -1);
	}
}

int	execution(t_command *t_cmd, t_simple_cmd *cmd)
{
	pid_t			pid;

	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			perror("Fork:");
		else if (pid == 0)
		{
			dup2(STDIN_FILENO, cmd->infile);
			dup2(STDOUT_FILENO, cmd->outfile);
			if (!cmd->full_path)
				is_builtin(t_cmd, cmd, cmd->first_token);
			else
			{
				if (execve(cmd->full_path, split_cmd(cmd), t_cmd->envp) == -1)
				{
					printf("%s: ", cmd->first_token);
					ft_error("Command Not Found", -1);
				}
			}
		}
		cmd = cmd->next;
	}
}
