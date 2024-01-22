/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:15:52 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/22 14:46:59 by smilosav         ###   ########.fr       */
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

/*void	add_token_hd(t_token **lst, t_token *new)
{
	t_token	*tmp;

	tmp = *lst;
	while (ft_strcmp(tmp->str, "<<"))
		tmp = tmp->next;
	printf("tmp: %s\n", tmp->str);
	tmp->next = new;
	new->prev = tmp->prev;
	//free_token(tmp);
	printf("tmp posle dodavanja: %s\n", tmp->str);
	printf("tmp->prev: %s\n", tmp->prev->str);
	printf("tmp->next: %s\n", tmp->next->str);
}*/

/*void	add_token_heredoc(char *delimiter, char *input, t_command *cmd_struct)
{
	t_token	*new_token;

	printf("delimiter: %s\n", delimiter);
	new_token = init_token(input, ARGUMENT);
	printf("new_token: %s\n", new_token->str);
	add_token_hd(&cmd_struct->first_token, new_token);
	
}*/

void	ft_here(char *delimiter, t_command *cmd_struct)
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
		//add_token_heredoc(delimiter, line, cmd_struct);
		i = strncmp(line, delimiter, ft_strlen(delimiter) + 1);
		if (i == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free_env(cmd_struct->lst_env);
	free(line);
	close(fd);
	exit(0);
}
int	exec_heredoc(char *delimiter, t_command *cmd_struct)
{
	int		pid;	

	pid = fork();
	if (pid == 0)
		ft_here(delimiter, cmd_struct);
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
			exec_heredoc(token->next->str, cmd_struct);
			token = token->next;
		}
		token = token->next;
	}
	return (1);
}
