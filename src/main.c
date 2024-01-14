/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:54:14 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/14 16:37:49 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	check_double_quotes(t_token *first_token)
{
	while (first_token)
	{
		var_not_double_quoted(first_token->str);
		first_token = first_token->next;
	}
}*/
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
		printf("Simple cmd %d:\n\n", i++);
		printf("Full path:%s\n", simple_cmd->full_path);
		printf("Infile:%d\n", simple_cmd->infile);
		printf("Outfile:%d\n", simple_cmd->outfile);
		print_command(simple_cmd->first_token);
		printf("\n");
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

void free_env(t_env *env)
{
	free_env_vars(env);
}

t_command	*process_input(char *str, t_command *cmd, t_env *env)
{
	cmd = tokenize(str, env);
	add_history(str);
	if (check_syntax(cmd) && expanding(cmd)
		&& delete_quotes(cmd)
		&& set_simple_commands(cmd)
		&& handle_redirections(cmd)
		&& check_options(cmd))
	{
		ft_exec(cmd);
		// print_simple_commands(cmd->first_cmd);
	}
	return (cmd);
}

/*int	end_minishell(t_command* cmd, t_env *env)
{
	clear_history();
	if (cmd)
		free(cmd);
	free_env(env);
	return (0);
}*/

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_env		*env;
	t_command	*cmd;

	(void)argc;
	(void)argv;

	env = get_env_vars(envp);
	cmd = NULL;
	while (1)
	{
		cmd = NULL;
		str = readline("minishell$ ");
		cmd = process_input(str, cmd, env);
		env = cmd->lst_env;
		if (cmd)
			free_cmd(cmd);
		free(str);
		//break ;
	}
	free_env(env);
	return (0);
}
