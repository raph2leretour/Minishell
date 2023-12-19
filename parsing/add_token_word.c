/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:44:34 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/19 11:37:54 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/include/libft.h"
#include "lexer.h"
#include <stdio.h>

//get the length of the word
//skip the quotes
int	word_len(char *cmd, int i)
{
	int		len;
	char	c;

	len = 0;
	while (cmd[i] && is_word(cmd[i]))
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			c = cmd[i];
			i++;
			len++;
			while (cmd[i] && cmd[i] != c)
			{
				i++;
				len++;
			}
		}
		if (cmd[i] && is_word(cmd[i]))
		{
			i++;
			len++;
		}
	}
	return (len);
}

//make a substring of a word we found in the input command
//initialize WORD token and add it to the back of the token list
//move i to after the word just added to the token list
int	add_token_word(t_command *cmd_struct, int i)
{
	int			len;
	char		*cmd;
	t_token		*new_token;

	len = word_len(cmd_struct->string, i);
	//printf("len: %d\n", len);
	cmd = ft_substr(cmd_struct->string, i, len);
	new_token = init_token(cmd, WORD);
	//printf("i: %d\n", i);
	i += len;
	//printf("i: %d\n", i);
	add_token(&cmd_struct->first_token, new_token);
	return (i);
}
