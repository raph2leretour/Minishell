/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:31:55 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/18 16:28:32 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*freeror(char **s_cmd)
{
	int	i;

	i = 0;
	while (s_cmd[i])
	{
		free(s_cmd[i]);
		i++;
	}
	free(s_cmd);
	return (NULL);
}

char	**split_cmd(t_simple_cmd *cmd)
{
	int		i;
	char 	**s_cmd;
	t_token	*token;

	token = cmd->first_token;
	i = 0;
	while (token && token->str)
	{
		i++;
	}
	s_cmd = malloc(sizeof(char *) * (i + 1));
	if (!s_cmd)
		return (ft_error("Cannot Malloc", -1), NULL);
	token = cmd->first_token;
	i = 0;
	while (token && token->str)
	{
		s_cmd[i] = ft_strdup(token->str);
		if (!s_cmd[i])
			return (ft_error("Cannot Malloc", -1), freeror(s_cmd));
		i++;
	}
	s_cmd[i] = NULL;
	return (s_cmd);
}
