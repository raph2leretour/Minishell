/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:26:07 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/23 22:02:38 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	check_redirections(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
	if (token_last(token)->type == REDIRECTION)
	{
		g_status = 2;
		ft_dprintf(2, "Syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}
