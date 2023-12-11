/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:11:42 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/11 16:26:27 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "lexer.h"

void	free_tokens(t_token *first_token)
{
	t_token	*tmp;

	while (first_token)
	{
		tmp = first_token->next;
		free(first_token->str);
		free(first_token);
		first_token = tmp;
	}
	free(first_token);
}

void	free_simple_cmd_tokens(t_token *first_token)
{
	t_token *tmp;

	while (first_token)
	{
		tmp = first_token->next;
		free(first_token);
		first_token = tmp;
	}
	free(first_token);
}
void	free_simple_cmds(t_simple_cmd *first_cmd)
{
	t_simple_cmd	*tmp;

	while (first_cmd)
	{
		tmp = first_cmd->next;
		free(first_cmd->full_path);
		free_simple_cmd_tokens(first_cmd->first_token);
		free(first_cmd);
		first_cmd = tmp;
	}
	free(first_cmd);
}

void	free_cmd(t_command *cmd)
{
	//if (cmd->string)
	//	free(cmd->string);
	if (cmd->first_token)
		free_tokens(cmd->first_token);
	if (cmd->first_cmd)
		free_simple_cmds(cmd->first_cmd);
	free(cmd);
}
