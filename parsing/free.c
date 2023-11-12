/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:11:42 by smilosav          #+#    #+#             */
/*   Updated: 2023/11/12 21:05:39 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/include/libft.h"
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

void	free_cmd(t_command *cmd)
{
	//if (cmd->string)
	//	free(cmd->string);
	if (cmd->first_token)
		free_tokens(cmd->first_token);
	free(cmd);
}
