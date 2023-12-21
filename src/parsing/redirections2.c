/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:56:47 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/21 20:59:48 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	redirect_output(char *file, int old_fd, t_command *cmd_struct)
{
	int	fd_out;
	
	if (old_fd > 2)
		close(old_fd);
	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_out == -1)
	{
		printf("minishell: %s: error creating the file\n", file);
		free_cmd(cmd_struct);
		exit (EXIT_FAILURE);
	}
	return (fd_out);
}

int	redirect_input(char *file, int old_fd, t_command *cmd_struct)
{
	int	fd_in;
	
	if (old_fd > 2)
		close(old_fd);
	fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
	{
		printf("minishell: %s:  No such file or directory\n", file);
		free_cmd(cmd_struct);
		exit (EXIT_FAILURE);
	}
	return (fd_in);
}

int	redirect_append(char *file, int old_fd, t_command *cmd_struct)
{
	int	fd_out;
	
	if (old_fd > 2)
		close(old_fd);
	fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_out == -1)
	{
		printf("minishell: %s: error creating the file\n", file);
		free_cmd(cmd_struct);
		exit (EXIT_FAILURE);
	}
	return (fd_out);
}

