/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:53:20 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/01 18:55:23 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait(pid_t last_pid)
{
	int		status;
	int		return_value;
	pid_t	pid;

	while (true)
	{
		pid = wait(&status);
		if (pid < 0)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				return_value = WEXITSTATUS(status);
			else
				return_value = 128 + WTERMSIG(status);
		}
	}
	return (return_value);
}
