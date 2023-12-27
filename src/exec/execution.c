/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:41:30 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/27 16:29:43 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_builtin(t_command *t_cmd, t_simple_cmd *cmd, t_token *token, int b)
{
	if (!ft_strncmp(token->str, "cd", 2))
	{
		if (token->next)
			cd(token->next->str, t_cmd->lst_env);
		else
			cd(NULL, t_cmd->lst_env);
	}
	else if (!ft_strncmp(token->str, "echo", 4))
		echo(split_cmd(cmd, 1), t_cmd->lst_env);
	else if (!ft_strncmp(token->str, "env", 3))
		ft_env(t_cmd->lst_env);
	else if (!ft_strncmp(token->str, "exit", 4))
		ft_exit(t_cmd, cmd->first_token->next);
	else if (!ft_strncmp(token->str, "export", 6))
		ft_export(t_cmd, cmd->first_token->next);
	else if (!ft_strncmp(token->str, "pwd", 3))
		pwd();
	else if (!ft_strncmp(token->str, "unset", 5))
		unset(t_cmd->lst_env, token->next->str);
	else
	{
		ft_dprintf(2, "%s: ", cmd->first_token->str);
		ft_error("Command Not Found", -1);
	}
	if (b)
		exit(EXIT_SUCCESS);
}

void	do_exec(t_simple_cmd *cmd, t_env *s_env)
{
	int		i;
	char	**c_env;
	char	**s_cmd;

	c_env = get_true_env(s_env);
	s_cmd = split_cmd(cmd, 0);
	if (execve(cmd->full_path, split_cmd(cmd, 0), c_env))
	{
		i = 0;
		free_array(c_env);
		free_array(s_cmd);
		ft_dprintf(2, "%s: ", cmd->first_token->str);
		ft_error("Command Not Found", -1);
	}
	i = 0;
	free_array(c_env);
}

int	execution(t_command *t_cmd, t_simple_cmd *cmd)
{
	pid_t	pid;

	while (cmd)
	{
		pid = fork();
		if (pid == -1)
		{
			close_fds(t_cmd->first_cmd);
			perror("Fork:");
			return (-1);
		}
		else if (pid == 0)
		{
			child_process(t_cmd, cmd);
		}
		if (cmd-> infile && cmd->infile > 2)
			close(cmd->infile);
		if (cmd->outfile && cmd->outfile > 2)
			close(cmd->outfile);
		cmd = cmd->next;
	}
	return (0);
}
