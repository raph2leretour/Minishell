/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:15:52 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 08:23:45 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_name(void)
{
	static int	i;
	char	*name;
	char	*nbr;

	nbr = ft_itoa(i);
	if (!nbr)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, nbr);
	free(nbr);
	i++;
	return (name);
}

bool	fill_heredoc(t_command *cmd, char *delimiter, int fd)
{
	char	*line;
	bool	ret;

	printf("cmd: %s\n", cmd->first_token->str);
	printf("delimitor :%s\n", delimiter);
	ret = false;
	line = NULL;
	while (1)
	{
		//set_signals_interactive();
		line = readline(">");
		//set_signals_noninteractive();
		//if (!evaluate_heredoc_line(cmd, &line, fd, &ret))
		//	break ;
		if (!strcmp(line, delimiter))
		{
			ret = true;
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	return (ret);
}

//unlink(simple_cmd->here_doc);
bool	get_heredoc_file(t_command *cmd, t_simple_cmd *simple_cmd, char *delimiter)
{
	int		tmp_fd;
	bool	ret;

	ret = true;
	tmp_fd = open(simple_cmd->here_doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(cmd, delimiter, tmp_fd);
	close(tmp_fd);
	return (ret);
}

int	heredoc(t_command *cmd)
{
	t_simple_cmd *simple_cmd;
	t_token	*token;

	//signal(SIGQUIT, &ft_child_sig);
	//signal(SIGINT, &ft_child_sig);
	simple_cmd = cmd->first_cmd;
	while (simple_cmd)
	{
		token = simple_cmd->first_token;
		while (token)
		{
			if (token->type == REDIRECTION && !ft_strcmp(token->str, "<<"))
			{
				simple_cmd->here_doc = get_heredoc_name();
				if (get_heredoc_file(cmd, simple_cmd, token->next->str))
				{
					simple_cmd->here_in = open(simple_cmd->here_doc,
						O_RDONLY);
				}
			}
			token = token->next;
		}
		simple_cmd = simple_cmd->next;
	}
	return (1);
}
