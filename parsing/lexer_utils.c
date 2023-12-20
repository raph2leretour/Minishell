/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 07:52:49 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/20 11:57:45 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_parenthesis(char c)
{
	if (c == '{' || c == '}'
		|| c == '(' || c == ')')
		return (1);
	return (0);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_word(char c)
{
	if (c != '|' && c != '&' && c != ';' && !is_redirection(c)
		&& !is_space(c) && !is_parenthesis(c))
		return (1);
	return (0);
}

int	is_builtin(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp("exit", str, ft_strlen(str)))
		return (2);
	if (!ft_strncmp("cd", str, ft_strlen(str)))
		return (1);
	else if (!ft_strncmp("echo", str, ft_strlen(str)))
		return (1);
	else if (!ft_strncmp("env", str, ft_strlen(str)))
		return (1);
	else if (!ft_strncmp("pwd", str, ft_strlen(str)))
		return (1);
	else if (!ft_strncmp("export", str, ft_strlen(str)))
		return (1);
	else if (!ft_strncmp("unset", str, ft_strlen(str)))
		return (1);
	return (0);
}

