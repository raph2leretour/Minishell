/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:09 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/20 13:58:47 by rtissera         ###   ########.fr       */
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
			ft_dprintf(2, "exit\nminishell: exit: %s: \
				numeric argument required\n", token->str);
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
			ft_dprintf(2, "exit\nminishell: exit: too many arguments\n");
			return ;
		}
		errno = ft_atoi(token->str);
		ft_dprintf(1, "exit\n");
		free_env(cmd->lst_env);
		free_cmd(cmd);
		exit(errno);
	}
	else
	{
		ft_dprintf(1, "exit\n");
		free_env(cmd->lst_env);
		free_cmd(cmd);
		exit(g_status);
	}
}
