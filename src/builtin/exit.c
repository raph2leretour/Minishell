/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:09 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/25 00:52:45 by rtissera         ###   ########.fr       */
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
			redirect_end(cmd->first_cmd);
			if (cmd)
				free_env(cmd->lst_env);
			free_cmd(cmd);
			exit(2);
		}
		i++;
	}
}

int	atouille(const char *nptr)
{
	int	res;
	int	sig;

	res = 0;
	sig = 1;
	while (((*nptr >= 9) && (*nptr <= 13)) || (*nptr == 32))
		nptr++;
	if (*nptr == 45)
	{
		sig *= -1;
		nptr++;
	}
	else if (*nptr == 43)
		nptr++;
	if (!ft_isdigit(*nptr))
		return (ft_dprintf(2, "exit: %s: numeric argument required\n", nptr), 2);
	while ((*nptr >= 48) && (*nptr <= 57))
	{
		if (!ft_isdigit(*nptr))
			return (ft_dprintf(2, "exit: %s: numeric argument required\n", \
			nptr), 2);
		res = (res * 10) + *nptr - 48;
		nptr++;
	}
	return (res * sig);
}

int	ft_exit(t_command *cmd, t_token *token)
{
	if (cmd && is_pipe(cmd))
		return (atouille(token->str));
	if (token && token->str)
	{
		is_arg_good(token, cmd);
		if (token->next && token->next->str)
			return (ft_dprintf(2, \
				"exit\nminishell: exit: too many arguments\n"), 2);
		g_status = atouille(token->str);
		ft_dprintf(1, "exit\n");
		redirect_end(cmd->first_cmd);
		if (cmd)
			free_env(cmd->lst_env);
		free_cmd(cmd);
		exit(g_status);
	}
	else
	{
		ft_dprintf(1, "exit\n");
		redirect_end(cmd->first_cmd);
		if (cmd)
			free_env(cmd->lst_env);
		free_cmd(cmd);
		exit(g_status);
	}
}
