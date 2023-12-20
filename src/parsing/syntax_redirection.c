/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:26:07 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/20 15:39:09 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_redirections(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
	if (token_last(token)->type == REDIRECTION)
	{
		printf("Syntax error near unexpected token `newline'\n");
		free_cmd(cmd_struct);
		exit(EXIT_FAILURE);
	}
	return (0);
}
