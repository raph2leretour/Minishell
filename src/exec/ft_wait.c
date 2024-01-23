/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:53:20 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/23 22:24:34 by rtissera         ###   ########.fr       */
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
			if (WIFEXITED(status))
			{
				g_status = WEXITSTATUS(status);
			}
			else
			{
				g_status = 128 + WTERMSIG(status);
				if (g_status == 131)
					ft_dprintf(2, "Quit (core dumped)\n");
			}
		}
	}
}
