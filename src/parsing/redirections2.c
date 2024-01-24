/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:56:47 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 20:18:13 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_output(char *file, int old_fd, t_command *cmd_struct)
{
	int	fd_out;

	(void ) cmd_struct;
	if (old_fd > 2)
		close(old_fd);
	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_out == -1)
		perror("minishell: Error");
	return (fd_out);
}

int	redirect_input(char *file, int old_fd, t_command *cmd_struct)
{
	int	fd_in;

	(void ) cmd_struct;
	if (old_fd > 2)
		close(old_fd);
	fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
		perror("minishell: Error");
	return (fd_in);
}

int	redirect_append(char *file, int old_fd, t_command *cmd_struct)
{
	int	fd_out;

	(void ) cmd_struct;
	if (old_fd > 2)
		close(old_fd);
	fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_out == -1)
		perror("minishell: Error");
	return (fd_out);
}
