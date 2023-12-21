/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:25:26 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/20 15:39:34 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


int	check_types(t_command *cmd_struct)
{
	t_token	*token;
	char	c;

	token = cmd_struct->first_token;
	while (token)
	{
		if (token->type == SEMI || (token->type == PIPE && ft_strlen(token->str) > 1) || (token->type == REDIRECTION && ft_strlen(token->str) > 2))
		{
			c = token->str[0];
			printf("Syntax error near unexpected token `%c'\n", c);
			free_cmd(cmd_struct);
			exit (EXIT_FAILURE);
		}
		token = token->next;
	}
	return (0);
}

int	check_pipe_location(t_command *cmd_struct)
{
	t_token	*token;
	//char	c;

	token = cmd_struct->first_token;
	if (token->type == PIPE || token_last(token)->type == PIPE)
	{
		//c = token->str[0];
		printf("Syntax error near unexpected token `|'\n");
		free_cmd(cmd_struct);
		exit (EXIT_FAILURE);
	}
	return (0);
}

void	check_syntax(t_command *cmd_struct)
{
	if (cmd_struct->first_token)
	{
		check_types(cmd_struct);
		check_quotes(cmd_struct);
		check_pipe_location(cmd_struct);
		check_between_pipes(cmd_struct);
		check_redirections(cmd_struct);
	}
}
