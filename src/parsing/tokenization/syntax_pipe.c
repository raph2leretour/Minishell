/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:50:19 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/23 21:59:35 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	check_between_pipes(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
	while (token)
	{
		if (token->type == PIPE && token->next && token->next->type == PIPE)
		{
			g_status = 2;
			ft_dprintf(2, "Syntax error near unexpected token `newline'\n");
			return (0);
		}
		token = token->next;
	}
	return (1);
}
