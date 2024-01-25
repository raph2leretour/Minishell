/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:22:52 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/25 02:30:10 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	basic_checks(char *token, int i, t_env *env_var)
{
	if (!contains_valid_var(token, i, env_var)
		&& dollar_quoted(token, i))
		return (0);
	if (!contains_valid_var(token, i, env_var)
		&& !dollar_quoted(token, i))
		return (1);
	if (contains_valid_var(token, i, env_var)
		&& !dollar_quoted(token, i)
		&& (token[i + 1] == '\'' || token[i + 1] == '"'))
		return (1);
	return (-1);
}

int	check_d_token_env(char *d_token, t_token *token, int i, t_env *env_var)
{
	char	*substr;

	substr = NULL;
	while (env_var)
	{
		substr = ft_strnstr(d_token, env_var->key, ft_strlen(d_token));
		if (substr != NULL)
		{
			if (wrong_var_form(token->str, i, env_var->key))
			{
				free(d_token);
				return (1);
			}
			else
			{
				free(d_token);
				return (0);
			}
		}
		env_var = env_var->next;
	}
	free(d_token);
	return (1);
}

int	contains_invalid_dollar(t_token *token, int i, t_env *env_var)
{
	int		j;
	char	*d_token;

	if (token->str[i + 1] == '?')
		return (0);
	if (basic_checks(token->str, i, env_var) != -1)
		return (basic_checks(token->str, i, env_var));
	j = get_len(token->str, i);
	d_token = ft_substr(token->str, i, j);
	if (!d_token[1] || (d_token[1] == '"' && !d_token[2])
		|| (d_token[1] == '\'' && !d_token[2]))
	{
		free (d_token);
		return (0);
	}
	return (check_d_token_env(d_token, token, i, env_var));
}

void	delete_invalid_var(t_token *token, int i)
{
	int		j;
	char	*before;
	char	*after;

	j = i + 1;
	while (token->str[j] && token->str[j] != '$' && token->str[j] != '\''
		&& token->str[j] != '"' && token->str[j] != '}')
	{
		if (token->str[j] == '{')
		{
			while (token->str[j] != '}')
			{
				j++;
			}
		}
		j++;
	}
	before = ft_substr(token->str, 0, i);
	after = ft_substr(token->str, j, ft_strlen(token->str));
	free(token->str);
	token->str = ft_strjoin(before, after);
	free(before);
	free(after);
}

int	check_quoted_dollar(int i, t_token *token, t_env *env_var)
{
	i++;
	while (token->str[i] != '"')
	{
		if (token->str[i] == '$')
		{
			if (contains_invalid_dollar(token, i, env_var))
			{
				delete_invalid_var(token, i);
				i--;
			}
		}
		i++;
	}
	return (i);
}
