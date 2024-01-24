/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:54:14 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 13:40:13 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	print_command(t_token *first_token)
{
	while (first_token)
	{
		printf("Token value: %s ;", first_token->str);
		printf("Token type: %d\n", first_token->type);
		first_token = first_token->next;
	}
}

void	print_simple_commands(t_simple_cmd *simple_cmd)
{
	int	i;

	i = 0;
	while (simple_cmd)
	{
		printf("--------------\n");
		printf("Simple cmd %d:\n", i++);
		printf("Full path:%s\n", simple_cmd->full_path);
		printf("Heredoc file: %s\n", simple_cmd->here_doc);
		printf("Heredoc fd: %d\n", simple_cmd->here_in);
		printf("Infile:%d\n", simple_cmd->infile);
		printf("Outfile:%d\n", simple_cmd->outfile);
		print_command(simple_cmd->first_token);
		ft_dprintf(1, "g_status = %d\n", g_status);
		printf("--------------\n");
		simple_cmd = simple_cmd->next;
	}
}

void	print_env(t_env *env_var)
{
	while (env_var)
	{
		printf("%s", env_var->key);
		printf("=");
		printf("%s\n", env_var->value);
		env_var = env_var->next;
	}
}

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
		//print_simple_commands(cmd->first_cmd);
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
	free_env(env);
	return (0);
}
