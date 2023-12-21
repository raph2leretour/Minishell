/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:56:37 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/21 20:58:44 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

void	set_redirection(char *redirection, char *file, t_simple_cmd *simple_cmd, t_command *cmd_struct)
{
	if (!ft_strncmp(redirection, ">", 1))
		simple_cmd->outfile = redirect_output(file, simple_cmd->outfile, cmd_struct);
	else if (!ft_strncmp(redirection, "<", 1))
		simple_cmd->infile = redirect_input(file, simple_cmd->infile, cmd_struct);
	else if (!ft_strncmp(redirection, ">>", 2))
		simple_cmd->outfile = redirect_append(file, simple_cmd->outfile, cmd_struct);
}

void	check_redirection(t_simple_cmd *simple_cmd, t_command *cmd_struct)
{
	t_token	*token;

	token = simple_cmd->first_token;
	while (token)
	{
		if (!token->next)
			break ;
		if (token->type == REDIRECTION && token->next->type == WORD)
		{
			set_redirection(token->str, token->next->str, simple_cmd, cmd_struct);
			token = token->next;
		}
		token = token->next;
	
	}
}

void	check_last_token(t_simple_cmd *simple_cmd, t_command *cmd_struct)
{
	t_token	*token;
	
	token = simple_cmd->first_token;
	if (token_last(token)->type == REDIRECTION)
	{
		printf("Syntax error near unexpected token `newline'\n");
		free_cmd(cmd_struct);
		exit(EXIT_FAILURE);
	}
}

void	handle_redirections(t_command *cmd_struct)
{
	t_simple_cmd	*simple_cmd;

	simple_cmd = cmd_struct->first_cmd;
	while (simple_cmd)
	{
		check_last_token(simple_cmd, cmd_struct);
		check_redirection(simple_cmd, cmd_struct);
		simple_cmd = simple_cmd->next;
	}
}
