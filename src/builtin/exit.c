/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:09 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/17 14:35:11 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_command *cmd)
{
	if (cmd->first_cmd->next || cmd->first_cmd->prev)
		return (1);
	return (0);
}

void	is_arg_good(t_token *token, t_command *cmd)
{
	int	i;

	i = 0;
	while (token->str[i])
	{
		if (!ft_isdigit(token->str[i]))
		{
			printf("exit\nbash: exit: %s: numeric argument required\n", \
				token->str);
			free_env(cmd->lst_env);
			free_cmd(cmd);
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
		is_arg_good(token, cmd);
		if (token->next && token->next->str)
		{
			printf("exit\nbash: exit: too many arguments\n");
			return ;
		}
		errno = ft_atoi(token->str);
		printf("exit\n");
		free_env(cmd->lst_env);
		free_cmd(cmd);
		exit(errno);
	}
	else
	{
		printf("exit\n");
		free_env(cmd->lst_env);
		free_cmd(cmd);
		exit(0);
	}
}
