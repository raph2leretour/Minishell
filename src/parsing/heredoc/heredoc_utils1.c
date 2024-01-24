/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:15:03 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 09:38:00 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*expand_heredoc(char *line, int i, t_env *env_var)
{
	int		j;
	char	*substr;
	char	*d_token;

	j = get_len(line, i);
	substr = NULL;
	d_token = ft_substr(line, i, j);
	while (env_var)
	{
		substr = ft_strnstr(d_token, env_var->key, ft_strlen(d_token));
		if (substr != NULL)
		{
			free(d_token);
			line = set_value_heredoc(line, i, env_var->value, env_var->key);
			return (line);
		}
		env_var = env_var->next;
	}
	return (line);
}

char	*exit_heredoc(char *line, int i)
{
	int		j;
	char	*before;
	char	*after;
	char	*var;
	char	*status;

	j = i + 1;
	before = ft_substr(line, 0, i);
	after = ft_substr(line, j + 1, ft_strlen(line));
	status = ft_itoa(g_status);
	var = ft_strjoin(status, after);
	free(line);
	line = ft_strjoin(before, var);
	free(before);
	free(after);
	free(var);
	free(status);
	return (line);
}

char	*delete_invalid_heredoc(char *line, int i)
{
	int		j;
	char	*before;
	char	*after;
	char	*del_line;

	j = i + 1;
	while (line[j] && line[j] != '$' && line[j] != '\''
		&& line[j] != '"' && line[j] != '}')
	{
		if (line[j] == '{')
		{
			while (line[j] != '}')
				j++;
		}
		j++;
	}
	before = ft_substr(line, 0, i);
	after = ft_substr(line, j, ft_strlen(line));
	free(line);
	del_line = ft_strjoin(before, after);
	free(before);
	free(after);
	return (del_line);
}

char	*get_expanded_line(t_command *cmd, char *line)
{
	int		i;
	char	*expanded_line;

	i = 0;
	expanded_line = line;
	while (expanded_line && expanded_line[i])
	{
		if (expanded_line[i] == '$')
		{
			if (contains_valid_var(expanded_line, i, cmd->lst_env))
				expanded_line = expand_heredoc(expanded_line, i, cmd->lst_env);
			else if (expanded_line[i + 1] == '?')
			{
				expanded_line = exit_heredoc(expanded_line, i);
				i--;
			}
			else
			{
				expanded_line = delete_invalid_heredoc(expanded_line, i);
				i--;
			}
		}
		i++;
	}
	return (expanded_line);
}

void	print_error(t_token *delimiter)
{
	g_status = 0;
	ft_dprintf(2, "warning: here-document delimited by end-of-file");
	ft_dprintf(2, " (wanted `%s')\n", delimiter->str);
}
