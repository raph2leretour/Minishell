/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 07:52:49 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/25 04:25:20 by rtissera         ###   ########.fr       */
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
	if (c != '|' && !is_redirection(c)
		&& !is_space(c))
		return (1);
	return (0);
}

int	is_builtin(char *str)
{
	if (str == NULL)
		return (1);
	if (!ft_strcmp("exit", str))
		return (2);
	if (!ft_strcmp("cd", str))
		return (1);
	else if (!ft_strcmp("echo", str))
		return (1);
	else if (!ft_strcmp("env", str))
		return (1);
	else if (!ft_strcmp("pwd", str))
		return (1);
	else if (!ft_strcmp("export", str))
		return (1);
	else if (!ft_strcmp("unset", str))
		return (1);
	return (0);
}
