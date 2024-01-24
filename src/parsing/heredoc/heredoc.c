/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:15:52 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 14:16:15 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	evaluate_heredoc_line(t_command *cmd, t_token *delimiter,
		char **line, bool *ret)
{
	if (*line == NULL)
	{
		print_error(delimiter);
		*ret = true;
		return (false);
	}
	if (!ft_strncmp(*line, delimiter->str, ft_strlen(delimiter->str) + 1))
	{
		*ret = true;
		return (false);
	}
	if (delimiter->type != DELIMITER && ft_strchr(*line, '$'))
	{
		*line = get_expanded_line(cmd, *line);
		if (!(*line))
		{
			free(*line);
			*ret = false;
			return (false);
		}
	}
	return (true);
}

bool	fill_heredoc(t_command *cmd, t_token *delimiter, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		line = readline(">");
		if (!evaluate_heredoc_line(cmd, delimiter, &line, &ret))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	return (ret);
}

bool	get_heredoc_file(t_command *cmd, t_simple_cmd *simple_cmd,
		t_token *delimiter)
{
	int		tmp_fd;
	bool	ret;

	ret = true;
	tmp_fd = open(simple_cmd->here_doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(cmd, delimiter, tmp_fd);
	close(tmp_fd);
	delimiter->type = ARGUMENT;
	return (ret);
}

int	heredoc(t_command *cmd)
{
	t_simple_cmd	*simple_cmd;
	t_token			*token;

	simple_cmd = cmd->first_cmd;
	while (simple_cmd)
	{
		token = simple_cmd->first_token;
		while (token)
		{
			if (token->type == REDIRECTION && !ft_strcmp(token->str, "<<"))
			{
				if (simple_cmd->here_doc != NULL)
				{
					if (simple_cmd->here_in != -1)
							close(simple_cmd->here_in);
					simple_cmd->here_in = -1;
					free(simple_cmd->here_doc);
				}
				simple_cmd->here_doc = get_heredoc_name();
				if (get_heredoc_file(cmd, simple_cmd, token->next))
					simple_cmd->here_in = open(simple_cmd->here_doc,
							O_RDONLY);
			}
			token = token->next;
		}
		simple_cmd = simple_cmd->next;
	}
	return (1);
}
