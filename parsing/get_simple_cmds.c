/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_simple_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:36:26 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/20 14:28:35 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/include/libft.h"
#include "lexer.h"
#include <stdio.h>

t_simple_cmd	*init_simple_cmd(t_token *head_tkn, t_command *cmd_struct)
{
	t_simple_cmd	*new_simple_cmd;

	new_simple_cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!new_simple_cmd)
		return (NULL);
	new_simple_cmd->full_path = NULL;
	if (!is_builtin(head_tkn->str))
		new_simple_cmd->full_path = get_cmd_path(head_tkn->str, cmd_struct);
	new_simple_cmd->infile =  0;
	new_simple_cmd->outfile = 0;
	new_simple_cmd->first_token = head_tkn;
	new_simple_cmd->prev = NULL;
	new_simple_cmd->next = NULL;
	return(new_simple_cmd);
}

t_command	*set_simple_commands(t_command *cmd_struct)
{
	t_token	*token;
	t_simple_cmd	*simple_cmd_struct;
	token = cmd_struct->first_token;
	while (token)
	{
		simple_cmd_struct = init_simple_cmd(init_token(token->str, token->type), cmd_struct);
		add_simple_cmd(&cmd_struct->first_cmd, simple_cmd_struct);
		token = token->next;
		while (token && token->type != PIPE)
		{
			add_token(&simple_cmd_struct->first_token, init_token(token->str, token->type));
			token = token->next;
		}
		if (token && token->type == PIPE)
			token = token->next;
	}
	return(cmd_struct);
}
