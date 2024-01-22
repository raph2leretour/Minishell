/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:11:15 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/22 10:07:10 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	var_key_len2(char *token, int i, char *key)
{
	char	*valid_var;
	char	*token_substr;
	int		token_substrlen;

	token_substr = ft_substr(token, i, ft_strlen(key) + 1);
	token_substrlen = ft_strlen(token_substr);
	valid_var = NULL;
	valid_var = ft_strjoin("$", key);
	if (!ft_strncmp(token_substr, valid_var, ft_strlen(valid_var)))
	{
		free(token_substr);
		free(valid_var);
		return (token_substrlen + i);
	}
	free (token_substr);
	free(valid_var);
	return (-1);
}

int	var_key_len(char *token, int i, char *key)
{
	char	*valid_var;
	char	*valid_var_p;
	char	*token_substr;
	int		token_substrlen;

	if (var_key_len2(token, i, key) != -1)
		return (var_key_len2(token, i, key));
	token_substr = ft_substr(token, i, ft_strlen(key) + 3);
	token_substrlen = ft_strlen(token_substr);
	valid_var_p = ft_strjoin(key, "}");
	valid_var = ft_strjoin("${", valid_var_p);
	if (!ft_strncmp(token_substr, valid_var, ft_strlen(valid_var)))
	{
		free(token_substr);
		free(valid_var);
		free(valid_var_p);
		return (token_substrlen + i);
	}
	return (1);
}

void	set_value(t_token *token, int i, char *value, char *key)
{
	int		j;
	char	*before;
	char	*after;
	char	*var;

	j = var_key_len(token->str, i, key);
	before = ft_substr(token->str, 0, i);
	after = ft_substr(token->str, j, ft_strlen(token->str));
	var = ft_strjoin(value, after);
	free(token->str);
	token->str = ft_strjoin(before, var);
	free(before);
	free(after);
	free(var);
}

void	expand_var(t_token *token, int i, t_env *env_var)
{
	int		j;
	char	*substr;
	char	*d_token;

	
	j = get_len(token->str, i);
	substr = NULL;
	d_token = ft_substr(token->str, i, j);
	while (env_var)
	{
		substr = ft_strnstr(d_token, env_var->key, ft_strlen(d_token));
		if (substr != NULL)
		{
			free(d_token);
			set_value(token, i, env_var->value, env_var->key);
			return ;
		}
		env_var = env_var->next;
	}
	free (d_token);
}

int	expand_quoted(int i, t_token *token, t_env *env_var)
{
	i++;
	while (token->str[i] != '"')
	{
		if (token->str[i] == '$')
		{
			if (is_dollar_exit(token, i))
			{
				expand_exit(token, i);
				//i--;
			}
			if (contains_valid_var(token->str, i, env_var))
			{
				expand_var(token, i, env_var);
				i--;
			}
		}
		i++;
	}
	return (i);
}
