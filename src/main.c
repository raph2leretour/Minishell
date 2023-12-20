/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:54:14 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/20 16:02:48 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		simple_cmd = simple_cmd->next;
	}
}

void	print_env(t_env *env_var)
{
	int	i;

	i = 0;
	while (env_var)
	{
		printf("%s", env_var->key);
		printf("=");
		printf("%s\n", env_var->value);
		env_var = env_var->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	// char	**tokens;
	int	i;
	t_command	*cmd;

	(void)argc;
	(void)argv;
	i = 0;
	/*while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}*/

	while (1)
	{
		str = readline("minishell$ ");
		//add_history(str);
		cmd = tokenize(str);
		get_env_vars(cmd, envp);
		check_syntax(cmd);
		//expand(cmd);
		set_simple_commands(cmd);
		printf("\n-----------Tokenization:----------\n");
		print_command(cmd->first_token);
		printf("\n-----------Simple commands:----------\n");
		print_simple_commands(cmd->first_cmd);
		printf("\n-----------Environment variables:----------\n");
		print_env(cmd->lst_env);
		printf("\n\n\n");
		free_cmd(cmd);
		free(str);
	}
	return (0);
}
