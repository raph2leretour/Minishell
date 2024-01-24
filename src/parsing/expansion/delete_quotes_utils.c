/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:19:55 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 20:19:44 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	no_more_quotes(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

void	check_quoted_delimiter(t_token *token)
{
	char	*d;
	int		i;

	d = token->str;
	i = 0;
	while (d[i])
	{
		if (d[i] == '\'' || d[i] == '"')
			token->type = DELIMITER;
		i++;
	}
	return ;
}
