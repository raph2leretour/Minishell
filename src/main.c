/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:54:14 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 20:02:16 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	free_env(t_env *env)
{
	free_env_vars(env);
}

t_command	*process_input(char *str, t_command *cmd, t_env *env)
{
	cmd = tokenize(str, env);
	add_history(str);
	if (check_syntax(cmd) && expanding(cmd)
		&& handle_backslash(cmd) && delete_quotes(cmd)
		&& check_executables(cmd)
		&& set_simple_commands(cmd)
		&& handle_redirections(cmd)
		&& set_option_type(cmd->first_cmd)
		&& heredoc(cmd))
	{
		ft_exec(cmd);
	}
	return (cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_env		*env;
	t_command	*cmd;

	(void)argc;
	(void)argv;
	env = get_env_vars(envp);
	cmd = NULL;
	g_status = 0;
	while (1)
	{
		signals();
		str = readline("minishell$ ");
		if (!str)
		{
			free_env(env);
			ft_exit(NULL, NULL);
		}
		cmd = process_input(str, cmd, env);
		env = cmd->lst_env;
		if (cmd)
			free_cmd(cmd);
		free(str);
	}
	return (0);
}
