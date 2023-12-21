/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:09 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/21 16:01:48 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_command *cmd)
{
}

int	is_exit(t_command *cmd)
{
}

void	ft_exit(t_command *cmd, t_token *token)
{
	int	i;

	if (strn && strn[0])
	{
		i = 0;
		while (strn[i])
		{
			if (!ft_isdigit(strn[i]))
				exit(2);
			i++;
		}
		errno = ft_atoi(strn);
		exit(errno);
	}
	else
		exit(0);
}
