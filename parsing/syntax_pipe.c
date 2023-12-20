/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:50:19 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/18 21:08:37 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	check_between_pipes(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
	while (token)
	{
		if (token->type == PIPE && token->next->type == PIPE)
		{
			printf("Syntax error near unexpected token `newline'\n");
			free_cmd(cmd_struct);
			exit(EXIT_FAILURE);
		}
		token = token->next;
	}
	return (0);
}
