/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:41:30 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/23 08:44:34 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_builtin(t_command *t_cmd, t_simple_cmd *cmd, t_token *token)
{
	if (!ft_strncmp(token->str, "cd", 2))
		return (cd(token->next->str, t_cmd->lst_env));
	else if (!ft_strncmp(token->str, "echo", 4))
		return (echo(split_cmd(cmd)));
	else if (!ft_strncmp(token->str, "env", 3))
		return (ft_env(t_cmd->lst_env));
	else if (!ft_strncmp(token->str, "exit", 4))
		return (ft_exit(t_cmd, cmd->first_token->next));
	else if (!ft_strncmp(token->str, "export", 6))
		return (ft_export(t_cmd, cmd->first_token->next));
	else if (!ft_strncmp(token->str, "pwd", 3))
		return (pwd());
	else if (!ft_strncmp(token->str, "unset", 5))
		return (unset(t_cmd->lst_env, token->str));
	else
	{
		printf("%s: ", cmd->first_token->str);
		ft_error("Command Not Found", -1);
	}
}

void	do_exec(t_simple_cmd *cmd, t_env *s_env)
{
	int		i;
	char	**c_env;

	c_env = get_true_env(s_env);
	if (execve(cmd->full_path, split_cmd(cmd), c_env))
	{
		i = 0;
		while (c_env[i])
		{
			free(c_env[i]);
			i++;
		}
		free(c_env);
		printf("%s: ", cmd->first_token->str);
		ft_error("Command Not Found", -1);
	}
	i = 0;
	while (c_env[i])
	{
		free(c_env[i]);
		i++;
	}
	free(c_env);
}

int	execution(t_command *t_cmd, t_simple_cmd *cmd)
{
	pid_t	pid;

	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			perror("Fork:");
		else if (pid == 0)
		{
			dup2(STDIN_FILENO, cmd->infile);
			dup2(STDOUT_FILENO, cmd->outfile);
			if (is_builtin(cmd->full_path))
				do_builtin(t_cmd, cmd, cmd->first_token);
			else
				do_exec(cmd, t_cmd->lst_env);
		}
		cmd = cmd->next;
	}
	return (0);
}
