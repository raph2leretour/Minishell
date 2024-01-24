/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:34:12 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/23 18:57:32 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_valid_var(char *token, int i, t_env *env_var)
{
	char	*sub_str;

	token = ft_substr(token, i, ft_strlen(token) - i);
	if (!is_name(token[1]) && token[1] != '{')
	{
		free (token);
		return (0);
	}
	sub_str = NULL;
	while (env_var)
	{
		sub_str = ft_strnstr(token, env_var->key, ft_strlen(token));
		if (sub_str != NULL)
		{
			free(token);
			return (1);
		}
		env_var = env_var->next;
	}
	free(token);
	return (0);
}

//if it's not $env->key  ${env->key} => no expansion
//if '$env->key' || '${env->key}' => no expansion
//if $'env->key' => env_key (no expansion)
//if ${'env->key'} => bash : bad substitution
int	wrong_var_form(char *token, int i, char *key)
{
	char	*valid_var;
	char	*valid_var_p;
	char	*token_substr;

	token_substr = ft_substr(token, i, ft_strlen(key) + 1);
	valid_var = NULL;
	valid_var = ft_strjoin("$", key);
	if (check_form1(token_substr, valid_var, token, i))
		return (0);
	token_substr = ft_substr(token, i, ft_strlen(key) + 3);
	valid_var_p = ft_strjoin(key, "}");
	valid_var = ft_strjoin("${", valid_var_p);
	if (check_form2(token_substr, valid_var, token))
	{
		free(valid_var_p);
		return (0);
	}
	free(valid_var_p);
	return (1);
}

//check if token contains $not_var or ${not_var} outside single quotes
//if it has invalid $, delete it
//function too long
void	delete_invalid_dollar(t_token *token, t_env *env_var)
{
	int	i;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\'')
		{
			i++;
			while (token->str[i] != '\'')
				i++;
		}
		if (token->str[i] == '"')
			i = check_quoted_dollar(i, token, env_var);
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
}

void	expand(t_token *token, t_env *env_var)
{
	int	i;

	i = 0;
	while (token->str && token->str[i])
	{
		if (token->str[i] == '\'')
		{
			i++;
			while (token->str[i] != '\'')
				i++;
		}
		if (token->str[i] == '"')
			i = expand_quoted(i, token, env_var);
		if (token->str[i] == '$')
		{
			if (is_dollar_exit(token, i))
				expand_exit(token, i);
			if (contains_valid_var(token->str, i, env_var))
			{
				expand_var(token, i, env_var);
				i--;
			}
		}
		i++;
	}
}

//Go through tokens, check if it contains a variable,
//check if variable is quoted
int	expanding(t_command *cmd_struct)
{
	t_env			*env_struct;
	t_token			*token;

	env_struct = cmd_struct->lst_env;
	token = cmd_struct->first_token;
	while (token)
	{
		if (token->prev && token->prev->type == REDIRECTION
			&& !ft_strncmp(token->prev->str, "<<", ft_strlen(token->prev->str)))
			token = token->next;
		if (token && token->type == ARGUMENT)
		{
			delete_invalid_dollar(token, env_struct);
			if (token->str[0] != '\0')
				expand(token, env_struct);
		}
		if (token)
			token = token->next;
	}
	return (1);
}
