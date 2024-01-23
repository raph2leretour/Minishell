/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:53:20 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/22 22:45:34 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(pid_t last_pid)
{
	int		status;
	pid_t	pid;

	while (true)
	{
		pid = wait(&status);
		if (pid < 0)
			break ;
		if (pid == last_pid)
		{
			ft_dprintf(1, "here\n");
			if (WIFEXITED(status))
			{
				ft_dprintf(1, "wexitstatus\n");
				g_status = WEXITSTATUS(status);
			}
			else
			{
				ft_dprintf(1, "wtermsig\n");
				g_status = 128 + WTERMSIG(status);
			}
		}
	}
}
