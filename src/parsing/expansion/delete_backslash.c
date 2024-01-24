/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:56:56 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/23 18:56:50 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	delete_backslash(int i, t_token *token)
{
	char	*before;
	char	*after;

	before = ft_substr(token->str, 0, i);
	after = ft_substr(token->str, i + 1, ft_strlen(token->str));
	free(token->str);
	token->str = ft_strjoin(before, after);
	free(before);
	free(after);
	if (i++ == '\\')
		i++;
	return (i);
}

void	delete_token_backslash(t_token *token)
{
	int	i;
	int	s_flag;
	int	d_flag;

	i = 0;
	s_flag = 0;
	d_flag = 0;
	while (token->str[i])
	{	
		if (token->str[i] == '\'')
			s_flag = change_flag(s_flag);
		if (token->str[i] == '"')
			d_flag = change_flag(d_flag);
		if (token->str[i] == '\\' && !s_flag && !d_flag)
			i = delete_backslash(i, token);
		if (token->str[i])
			i++;
	}
}

int	handle_backslash(t_command *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		delete_token_backslash(token);
		token = token->next;
	}
	return (1);
}
