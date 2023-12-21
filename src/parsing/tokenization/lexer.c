/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:36:16 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/20 15:59:30 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//initialize token
t_token	*init_token(char *value, int type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = value;
	new_token->type = type;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

//initialize command
t_command	*init_command(char *value)
{
	t_command	*new_command;

	new_command = (t_command *)malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->string = value;
	new_command->first_token = NULL;
	new_command->first_cmd = NULL;
	new_command->lst_env = NULL;
	return (new_command);
}

/*Get the input and create tokens out of the strings, and add them to
the command structure as a doubly linked list*/
t_command	*tokenize(char *input_cmd)
{
	int		i;
	int		len;
	t_command	*cmd_struct;

	input_cmd = ft_strtrim(input_cmd, " ");
	cmd_struct = init_command(input_cmd);
	printf("\nInput command: %s\n\n", cmd_struct->string);
	i = 0;
	len = ft_strlen(cmd_struct->string);
	while (i < len && cmd_struct->string[i])
	{
		while (is_space(cmd_struct->string[i]))
			i++;
		if (is_word(cmd_struct->string[i]))
			i = add_token_word(cmd_struct, i);
		if (is_redirection(cmd_struct->string[i]))
			i = add_token_redirection(cmd_struct, i);
		if (is_parenthesis(cmd_struct->string[i]))
			i = add_token_parenthesis(cmd_struct, i);
		if (cmd_struct->string[i] == '|')
			i = add_token_pipe(cmd_struct, i);
		if (cmd_struct->string[i] == '&')
			i = add_token_and(cmd_struct, i);
		if (cmd_struct->string[i] == ';')
			i = add_token_semi(cmd_struct, i);
	}
	free(input_cmd);
	return (cmd_struct);
}
