/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:09 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/21 18:05:23 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_command *cmd)
{
	if (cmd->first_cmd->next || cmd->first_cmd->prev)
		return (1);
	return (0);
}

void	is_arg_good(t_token *token)
{
	int	i;

	i = 0;
	while (token->str[i])
	{
		if (!ft_isdigit(token->str[i]))
		{
			printf("exit\nbash: exit: %s: numeric argument required\n", token->str);
			exit(2);
		}
		i++;
	}
}

void	ft_exit(t_command *cmd, t_token *token)
{
	if (is_pipe(cmd))
		return ;
	if (token && token->str)
	{
		is_arg_good(token);
		if (token->next && token->next->str)
		{
			printf("exit\nbash: exit: too many arguments\n");
			return ;
		}
		errno = ft_atoi(token->str);
		printf("exit\n");
		exit(errno);
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
