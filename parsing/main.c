/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:54:14 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/05 14:48:21 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/include/libft.h"
#include "lexer.h"

void	print_command(t_token *first_token)
{
	while (first_token)
	{
		printf("Token value: %s ;", first_token->str);
		printf("Token type: %d\n", first_token->type);
		first_token = first_token->next;
	}
}

int	main(void)
{
	char	*str;
	char	**tokens;
	int	i;
	t_command	*cmd;

	i = 0;
	while (1)
	{	
		str = readline("minishell$ ");
		//add_history(str);
		cmd = tokenize(str);
		/*check_syntax(cmd);
		expand(cmd);
		get_simple_commands(cmd);*/
		print_command(cmd->first_token);
		free_cmd(cmd);
		free(str);
	}
	return (0);
}
