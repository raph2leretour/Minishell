/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:26:34 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 08:51:30 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

void	substr_and_join(t_token *token, int q_open, int q_close)
{
	char	*before;
	char	*after;
	char	*inside;
	char	*join;

	inside = ft_substr(token->str, q_open + 1, q_close - q_open - 1);
	before = ft_substr(token->str, 0, q_open);
	after = ft_substr(token->str, q_close + 1, ft_strlen(token->str));
	join = ft_strjoin(before, inside);
	free(token->str);
	token->str = ft_strjoin(join, after);
	free(before);
	free(after);
	free(inside);
	free(join);
}

int	i_single(int i, t_token *token, int q_close, int q_open)
{
	q_open = i;
	i++;
	while (token->str[i] != '\'')
		i++;
	q_close = i;
	substr_and_join(token, q_open, q_close);
	i = q_close - 1;
	return (i);
}

int	i_double(int i, t_token *token, int q_close, int q_open)
{
	q_open = i;
	i++;
	while (token->str[i] != '"')
		i++;
	q_close = i;
	substr_and_join(token, q_open, q_close);
	i = q_close - 1;
	return (i);
}

void	delete_token_quotes(t_token *token)
{
	int	i;
	int	q_open;
	int	q_close;

	i = 0;
	q_open = 0;
	q_close = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\'')
			i = i_single(i, token, q_close, q_open);
		if (token->str[i] == '"')
			i = i_double(i, token, q_close, q_open);
		if (no_more_quotes(token->str, i))
			return ;
		if (!no_more_quotes(token->str, i)
			&& token->str[i] != '"' && token->str[i] != '\'')
			i++;
	}
}

void	check_quoted_delimiter(t_token *token)
{
	char	*d = token->str;
	int	i;

	i = 0;
	while (d[i])
	{
		if (d[i] == '\'' || d[i] == '"')
			token->type = DELIMITER;
		i++;
	}
	return ;
}
int	delete_quotes(t_command *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->prev && token->prev->type == REDIRECTION
			&& !ft_strncmp(token->prev->str, "<<", ft_strlen(token->prev->str)))
		{
			check_quoted_delimiter(token);
		}
		if (token)
		{
			delete_token_quotes(token);
			token = token->next;
		}
	}
	return (1);
}
