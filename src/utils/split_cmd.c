/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:31:55 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/17 20:16:07 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iterator(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->str)
	{
		token = token->next;
		i++;
	}
	return (i);
}

char	**freeror(char **s_cmd)
{
	int	i;

	i = 0;
	while (s_cmd[i])
	{
		free(s_cmd[i]);
		i++;
	}
	free(s_cmd);
	return (malloc(0));
}

char	**split_cmd(t_simple_cmd *cmd, bool skip)
{
	int		i;
	char	**s_cmd;
	t_token	*token;

	token = cmd->first_token;
	if (skip)
		token = token->next;
	i = iterator(token);
	s_cmd = malloc(sizeof(char *) * (i + 2));
	if (!s_cmd)
		return (ft_error("Cannot Malloc", -1), NULL);
	token = cmd->first_token;
	i = 0;
	while (token && token->str && \
		(token->type == COMMAND || token->type == ARGUMENT
		|| token->type == OPTION))
	{
		s_cmd[i] = ft_strdup(token->str);
		if (!s_cmd[i])
			return (ft_error("Cannot Malloc", -1), freeror(s_cmd));
		token = token->next;
		i++;
	}
	s_cmd[i] = NULL;
	return (s_cmd);
}
