/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:26:34 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/01 15:27:44 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"
void	delete_single_quotes(t_token *token, int q_open, int q_close)
{
	char	*before;
	char	*after;
	char	*inside;
	char	*join;

	//printf("q_open: %d, q_close: %d\n", q_open, q_close);
	inside = ft_substr(token->str, q_open + 1, q_close - q_open - 1);
	before = ft_substr(token->str, 0, q_open);
	after = ft_substr(token->str, q_close + 1, ft_strlen(token->str));
	//printf("before:%s:\n", before);
	//printf("after:%s:\n", after);
	//printf("inside:%s:\n", inside);
	join = ft_strjoin(before, inside);
	free(token->str);
	token->str = ft_strjoin(join, after);
	free(before);
	free(after);
	free(join);
	//printf("token->str:%s:\n", token->str);
}

void	delete_double_quotes(t_token *token, int q_open, int q_close)
{
	char	*before;
	char	*after;
	char	*inside;
	char	*join;

	//printf("q_open: %d, q_close: %d\n", q_open, q_close);
	inside = ft_substr(token->str, q_open + 1, q_close - q_open - 1);
	before = ft_substr(token->str, 0, q_open);
	after = ft_substr(token->str, q_close + 1, ft_strlen(token->str));
	//printf("before:%s:\n", before);
	//printf("after:%s:\n", after);
	//printf("inside:%s:\n", inside);
	join = ft_strjoin(before, inside);
	free(token->str);
	token->str = ft_strjoin(join, after);
	free(before);
	free(after);
	free(join);
	//printf("token->str:%s:\n", token->str);
}

int	no_more_quotes(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (0);
		i++;
	}
	return (1);
}
void	delete_token_quotes(t_token *token)
{
	int	i;
	int	q_open;
	int	q_close;
	
	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\'')
		{
			q_open = i;
			i++;
			while (token->str[i] != '\'')
				i++;
			q_close = i;
			delete_single_quotes(token, q_open, q_close);
			i = q_close - 1;
			//printf("i posle ': %d\n", i);
		}
		if (token->str[i] == '"')
		{
			q_open = i;
			i++;
			while (token->str[i] != '"')
				i++;
			q_close = i;
			delete_single_quotes(token, q_open, q_close);
			i = q_close - 1;
			//printf("i posle \": %d\n", i);
		}
		if (no_more_quotes(token->str, i))
			return ;
		if (!no_more_quotes(token->str, i) && token->str[i] != '"' && token->str[i] != '\'')
			i++;
		
	}
}

int	delete_quotes(t_command *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		delete_token_quotes(token);
		token = token->next;
	}
	return (1);
}
