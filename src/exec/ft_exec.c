/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:35:17 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/18 15:01:48 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_command *t_cmd)
{
	int	status;
	int	return_value;

	create_pipe(t_cmd);
	execution(t_cmd);
	while (waitpid(-1, &status, 0) == -1)
	{
		if (WIFEXITED(status))
		{
			return_value = status;
		}
	}
	clear_pipes(t_cmd);
}
