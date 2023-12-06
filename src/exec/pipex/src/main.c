/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:57:53 by rtissera          #+#    #+#             */
/*   Updated: 2023/06/27 11:19:23 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(char **av, char **env, int fd[2])
{
	int	infile;

	infile = open(av[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error();
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(infile);
	execificator(av[2], env, fd);
}

void	parent_process(char **av, char **env, int fd[2])
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error();
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execificator(av[3], env, fd);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid1;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			child_process(av, env, fd);
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			parent_process(av, env, fd);
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
	}
	else
		ft_printf("Error: Bad arguments");
	return (0);
}
