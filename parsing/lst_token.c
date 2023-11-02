/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:39:37 by smilosav          #+#    #+#             */
/*   Updated: 2023/11/02 22:40:59 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

//return the last token in the list
t_token	*token_last(t_token *lst)
{
	t_token	*aux;

	if (lst == NULL)
		return (lst);
	aux = lst;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

//add token to the back of the list
void	add_token(t_token **lst, t_token *new_token)
{
	t_token	*tmp;

	if (new_token == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_token;
		return ;
	}
	tmp = token_last(*lst);
	tmp->next = new_token;
	new_token->prev = tmp;
}
