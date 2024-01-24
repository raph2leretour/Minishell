/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:01:05 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/23 22:01:54 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/include/libft.h"
#include "lexer.h"

int	change_flag(int flag)
{
	if (flag == 0)
		return (1);
	if (flag == 1)
		return (0);
	return (0);
}

int	check_single(char *word, int i)
{
	int	flag;

	flag = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			flag = change_flag(flag);
		i++;
	}
	if (flag == 0)
	{
		while (word[i - 1] != '\'')
			i--;
		return (i);
	}
	else
	{
		g_status = 2;
		ft_dprintf(2, "minishell: single quotes not closed\n");
		return (-1);
	}
}

int	check_double(char *word, int i)
{
	int	flag;

	flag = 0;
	while (word[i])
	{
		if (word[i] == '"')
			flag = change_flag(flag);
		i++;
	}
	if (flag == 0)
	{
		while (word[i - 1] != '"')
			i--;
		return (i);
	}
	else
	{
		g_status = 2;
		ft_dprintf(2, "minishell: double quotes not closed\n");
		return (-1);
	}
}

int	check_if_all_quotes_closed(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		while (word[i] && word[i] != '"' && word[i] != '\'')
			i++;
		if (word[i] == '"')
			i = check_double(word, i);
		if (i == -1)
			return (0);
		if (word[i] == '\'')
			i = check_single(word, i);
		if (i == -1)
			return (0);
	}
	return (1);
}

int	check_quotes(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
	while (token)
	{
		if (token->type == ARGUMENT)
		{
			if (!check_if_all_quotes_closed(token->str))
				return (0);
		}
		token = token->next;
	}
	return (1);
}
