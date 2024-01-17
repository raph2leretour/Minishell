/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:15:52 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/17 22:18:02 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	ft_here_sig(int signal)
{
	if (signal == SIGINT)
		exit(1);
}

static void	ft_child_sig(int signal)
{
	if (signal == SIGINT)
		printf("\n");
}

void	ft_here(char *delimiter)
{
	int		i;
	int		fd;
	char	*line;

	fd = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_here_sig);
		line = readline("> ");
		if (!line)
		{
			printf("warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			close(fd);
			exit(0);
		}
		i = strncmp(line, delimiter, ft_strlen(delimiter) + 1);
		if (i == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}
int	exec_heredoc(char *delimiter)
{
	int		pid;	

	pid = fork();
	if (pid == 0)
		ft_here(delimiter);
	waitpid(pid, &g_status, 0);
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	return (g_status);
}

int	heredoc(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
	signal(SIGQUIT, &ft_child_sig);
	signal(SIGINT, &ft_child_sig);
	while (token)
	{
		if (token->type == REDIRECTION && !ft_strncmp(token->str, "<<", 2))
		{
			exec_heredoc(token->next->str);
			printf("<<%s\n", token->next->str);
			token = token->next;
		}
		token = token->next;
	}
	return (1);
}
