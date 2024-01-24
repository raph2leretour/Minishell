/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:15:52 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 19:41:22 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	evaluate_heredoc_line(t_command *cmd, t_token *delimiter,
		char **line, int *ret)
{
	if (*line == NULL)
	{
		print_error(delimiter);
		*ret = 0;
		return (1);
	}
	if (!ft_strncmp(*line, delimiter->str, ft_strlen(delimiter->str) + 1))
	{
		*ret = 0;
		return (1);
	}
	if (delimiter->type != DELIMITER && ft_strchr(*line, '$'))
	{
		*line = get_expanded_line(cmd, *line);
		if (!(*line))
		{
			free(*line);
			*ret = 1;
			return (1);
		}
	}
	return (0);
}

int	fill_heredoc(t_command *cmd, t_token *delimiter, int fd)
{
	const int	old_in_fd = dup(STDIN_FILENO);
	char		*line;
	int		ret;

	if (old_in_fd <= -1)
		return (3);
	ret = 0;
	line = NULL;
	hd_signal_mode();
	errno = 0;
	while (1)
	{
		line = readline(">");
		if (errno == 9 || evaluate_heredoc_line(cmd, delimiter, &line, &ret))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (errno == 9)
		ret = 2;
	free(line);
	if (dup2(old_in_fd, STDIN_FILENO) < 0)
		ret = 3;
	close(old_in_fd);
	return (ret);
}

int	get_heredoc_file(t_command *cmd, t_simple_cmd *simple_cmd,
		t_token *delimiter)
{
	int	tmp_fd;
	int	ret;

	ret = 0;
	ft_dprintf(2, "%s\n", simple_cmd->here_doc);
	tmp_fd = open(simple_cmd->here_doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(cmd, delimiter, tmp_fd);
	close(tmp_fd);
	delimiter->type = ARGUMENT;
	return (ret);
}

void	create_heredoc_file(t_command *cmd, t_simple_cmd *simple_cmd, \
	t_token *token, int *ret)
{
	if (simple_cmd->here_doc != NULL)
	{
		if (simple_cmd->here_in != -1)
				close(simple_cmd->here_in);
		simple_cmd->here_in = -1;
		free(simple_cmd->here_doc);
	}
	simple_cmd->here_doc = get_heredoc_name();
	*ret = get_heredoc_file(cmd, simple_cmd, token->next);
	if (*ret == 0)
		simple_cmd->here_in = open(simple_cmd->here_doc,
				O_RDONLY);
}

int	heredoc(t_command *cmd)
{
	t_simple_cmd	*simple_cmd;
	t_token			*token;
	int				ret = 0;

	simple_cmd = cmd->first_cmd;
	while (simple_cmd && ret <=1)
	{
		token = simple_cmd->first_token;
		while (token && ret <=1)
		{
			if (token->type == REDIRECTION && !ft_strcmp(token->str, "<<"))
				create_heredoc_file(cmd, simple_cmd, token, &ret);
			token = token->next;
		}
		simple_cmd = simple_cmd->next;
	}
	return (ret <= 1);
}
