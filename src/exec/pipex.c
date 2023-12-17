/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:57:53 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/17 21:00:34 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(char **argv, char **envp, int fd[2])
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		close(fd[0]);
		close(fd[1]);
		ft_error(NULL, -1);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(infile);
	execificator(argv[2], envp, fd);
}

void	parent_process(char **argv, char **envp, int fd[2])
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		close(fd[0]);
		close(fd[1]);
		ft_error(NULL, -1);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execificator(argv[3], envp, fd);
}

int	pipex(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (pipe(fd) == -1)
		ft_error(NULL, -1);
	pid1 = fork();
	if (pid1 == -1)
		ft_error(NULL, -1);
	if (pid1 == 0)
		child_process(argv, envp, fd);
	pid1 = fork();
	if (pid1 == -1)
		ft_error(NULL, -1);
	if (pid1 == 0)
		parent_process(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
