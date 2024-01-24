/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:07:55 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 09:54:12 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_name(char c)
{
	if ((c > 64 && c < 91) || (c > 47 && c < 58)
		|| c == '_' || (c > 96 && c < 123))
		return (1);
	return (0);
}

int	check_form1(char *token_substr, char *valid_var, char *token, int i)
{
	if (!ft_strcmp(token_substr, valid_var)
		&& (!token[ft_strlen(valid_var) + i]
			|| token[ft_strlen(valid_var) + i] == '$'
			|| token[ft_strlen(valid_var) + i] == '"'
			|| !is_word(token[ft_strlen(valid_var) + i])
			|| token[ft_strlen(valid_var) + i] == '}'
			|| token[ft_strlen(valid_var) + i] == '{'))
	{
		free(token_substr);
		free(valid_var);
		return (1);
	}
	else
	{
		free(token_substr);
		free(valid_var);
		return (0);
	}
}

int	check_form2(char *token_substr, char *valid_var, char *token)
{
	if (valid_var != NULL
		&& ft_strnstr(token_substr, valid_var, ft_strlen(token))
		&& (!token[ft_strlen(valid_var)]
			|| token[ft_strlen(valid_var)] == '$'
			|| token[ft_strlen(valid_var)] == '"'
			|| is_word(token[ft_strlen(valid_var)])))
	{
		free(token_substr);
		free(valid_var);
		return (1);
	}
	else
	{
		free(token_substr);
		free(valid_var);
		return (0);
	}
}

int	dollar_quoted(char *token, int i)
{
	int	j;
	int	d;

	j = i;
	d = 0;
	if (!token[i++] && !token[i--])
		return (0);
	if (!token[i++])
		return (1);
	if (!ft_strcmp(token, "\"$\""))
		return (1);
	while (j != -1)
	{
		if (token[j] == '"')
			d++;
		j--;
	}
	if (d == 0)
		return (0);
	if (d % 2 != 0 && d != 1)
		return (1);
	if (d == 0 && token[i + 1] == ' ')
		return (0);
	return (0);
}

int	get_len(char *token, int i)
{
	i++;
	while (token[i] && token[i] != '$' && token[i] != '\'' && token[i] != '"')
		i++;
	return (i);
}
