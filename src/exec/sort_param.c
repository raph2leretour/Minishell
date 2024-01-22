/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:13:18 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/22 20:08:35 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_on_top(t_token *token)
{
	t_token	*tmp;

	while (token && token->type != PIPE && \
		token->prev->type != COMMAND && token->prev->type != OPTION)
	{
		tmp = token->prev;
		token->prev = tmp->prev;
		tmp->prev->next = token;
		tmp->next = token->next;
		if (token->next)
			token->next->prev = tmp;
		token->next = tmp;
		tmp->prev = token;
	}
}

void	ft_karl(t_token *token)
{
	t_token	*head;

	head = token;
	while (token && (token->type == COMMAND || token->type == OPTION)
		&& token->type != PIPE)
		token = token->next;
	if (!token || !token->prev)
	{
		token = head;
		return ;
	}
	while (token && token->type != PIPE)
	{
		if (token->type == OPTION)
		{
			put_on_top(token);
		}
		token = token->next;
	}
	token = head;
}
