/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:36:16 by smilosav          #+#    #+#             */
/*   Updated: 2023/11/12 20:58:09 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/include/libft.h"
#include "lexer.h"
#include <stdio.h>

int	ft_is_builtin(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp("exit", str, ft_strlen(str)))
		return (2);
	if (!ft_strncmp("cd", str, ft_strlen(str)))
		return (1);
	else if (!ft_strncmp("echo", str, ft_strlen(str)))
		return (1);
	else if (!ft_strncmp("env", str, ft_strlen(str)))
		return (1);
	else if (!ft_strncmp("pwd", str, ft_strlen(str)))
		return (1);
	else if (!ft_strncmp("export", str, ft_strlen(str)))
		return (1);
	else if (!ft_strncmp("unset", str, ft_strlen(str)))
		return (1);
	return (0);
}

//set token type
void	init_type(t_token *new)
{
	int	len;

	len = 0;
	if (new->str)
		len = ft_strlen(new->str);
	if (len == 1)
	{
		if (new->str[0] == '<')
			new->type = INPUT;
		else if (new->str[0] == '>')
			new->type = OUTPUT;
		else if (new->str[0] == '|')
			new->type = PIPE;
	}
	if (len == 2)
	{
		if (new->str[0] == '<' && new->str[1] == '<')
			new->type = HERE_DOC;
		if (new->str[0] == '>' && new->str[1] == '>')
			new->type = APPEND;
	}
	if (ft_is_builtin(new->str))
		new->type = BUILTIN;
	if (new->type == NO_TYPE && len != 0)
		new->type = ARG;
}

//initialize token
t_token	*init_token(char *value)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token)); //leak
	if (!new_token)
		return (NULL);
	//new_token->str = (char *)malloc(sizeof(char) * ft_strlen(value) + 1);
	new_token->str = value;
	printf("Adresa new_token->str: %p\n", new_token->str);
	new_token->type = NO_TYPE;
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
	//new_command->string = (char *)malloc(sizeof(char) * ft_strlen(value) + 1);
	new_command->string = value;
	new_command->first_token = NULL;
	return (new_command);
}

/*1. Get the input and seperate the command
 into an array of strings
2. Create tokens out of the strings, and add them to 
the command structure as a doubly linked list*/
t_command	*tokenize(char *command)
{
	int			i;
	char		**tokens;
	t_command	*cmd_struct;
	t_token		*new_token;

	//command = ft_strtrim(command, " \t\r\v\f\n");
	cmd_struct = init_command(command);
	printf("\nInput command: %s\n\n", cmd_struct->string);
	tokens = ft_split(command, ' '); //leaks
	i = 0;
	while (tokens[i])
	{
		new_token = init_token(tokens[i]);
		printf("Adresa tokens[i]: %p\n", tokens[i]);
		init_type(new_token);
		add_token(&(cmd_struct->first_token), new_token);
		i++;
	}
	free(tokens);
	return (cmd_struct);
}
