/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:54:14 by smilosav          #+#    #+#             */
/*   Updated: 2023/11/02 22:44:32 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/include/libft.h"
#include "lexer.h"

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
		while (cmd->first_token)
		{
			printf("Token value: %s ;", cmd->first_token->str);
			printf("Token type: %d\n", cmd->first_token->type);
			cmd->first_token = cmd->first_token->next;
		}
		free(str);
	}
	return (0);
}
