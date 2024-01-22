/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:37:18 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/22 10:11:02 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	is_dollar_exit(t_token *token, int i)
{
	if (token->str[i + 1] == '?')
		return (1);
	return (0);
}

void	expand_exit(t_token *token, int i)
{
	int		j;
	char 	*before;
	char 	*after;
	char 	*var;
	char	*status;

	j = i + 1;
	before = ft_substr(token->str, 0, i);
	after = ft_substr(token->str, j + 1, ft_strlen(token->str));
	status = ft_itoa(g_status);
	var = ft_strjoin(status, after);
	free(token->str);
	token->str = ft_strjoin(before, var);
	free(before);
	free(after);
	free(var);
	free(status);
}
