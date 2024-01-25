/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:34:11 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/25 03:47:00 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_any_redirection(t_simple_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token && token->str)
	{
		if (is_redirection(token->str[0]))
			return (1);
		token = token->next;
	}
	return (0);
}
