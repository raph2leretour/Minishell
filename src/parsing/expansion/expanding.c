/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:34:12 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/01 15:38:45 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int 	is_name(char c)
{
	if ((c > 64 && c < 91) || (c > 47 && c < 58) || c == '_')
		return (1);
	return (0);
}
int	contains_valid_var(char *token, int i, t_env *env_var)
{
	char	*sub_str;
	token = ft_substr(token, i, ft_strlen(token) - i);
	//printf("token_contains_valid_var: %s\n", token);
	if (!is_name(token[1]) && token[1] != '{')
		return (0);
	//printf("token: %s\n", token);
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
	//printf("token_substr:%s:\n", token_substr);
	valid_var = NULL;
	valid_var = ft_strjoin("$", key);
	//printf("valid_var:%s:\n", valid_var);
	//printf("token[ft_strlen(valid_var)]:%c\n", token[ft_strlen(valid_var)]);
	//printf("token[ft_strlen(valid_var)]:%c\n", token[ft_strlen(valid_var) + i]);
	if (!ft_strncmp(token_substr, valid_var, ft_strlen(valid_var))
			&& (!token[ft_strlen(valid_var) + i]
				|| token[ft_strlen(valid_var) + i] == '$'
				|| token[ft_strlen(valid_var) + i] == '"'
				|| !is_word(token[ft_strlen(valid_var) + i])
				|| token[ft_strlen(valid_var) + i] == '}'
				|| token[ft_strlen(valid_var) + i] == '{'))
	{
		free(token_substr);
		free(valid_var);
		return (0);	
	}
	free(token_substr);
	free(valid_var);
	token_substr = ft_substr(token, i, ft_strlen(key) + 3);
	//printf("token_substr:%s:\n", token_substr);
	valid_var_p = ft_strjoin(key, "}");
	valid_var = ft_strjoin("${", valid_var_p);
	if (valid_var != NULL && ft_strnstr(token_substr, valid_var, ft_strlen(token))
			&& (!token[ft_strlen(valid_var)]
				||token[ft_strlen(valid_var)] == '$'
				|| token[ft_strlen(valid_var)] == '"'
				|| is_word(token[ft_strlen(valid_var)])))
	{
		free(token_substr);
		free(valid_var);
		free(valid_var_p);
		return (0);
	}
	free(token_substr);
	free(valid_var);
	free(valid_var_p);
	return (1);
	
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
	if (!ft_strncmp(token, "\"$\"", 3))
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

int	contains_invalid_dollar(t_token *token, int i, t_env *env_var)
{
	int	j;
	char	*substr;
	char	*d_token;

	if (!contains_valid_var(token->str, i, env_var)
			&& dollar_quoted(token->str, i))
		return (0);
	if (!contains_valid_var(token->str, i, env_var)
			&& !dollar_quoted(token->str, i))
		return (1);
	if (contains_valid_var(token->str, i, env_var)
			&& !dollar_quoted(token->str, i)
			&& (token->str[i + 1] == '\'' || token->str[i + 1] == '"'))
		return (1);
	j = get_len(token->str, i);
	substr = NULL;
	d_token = ft_substr(token->str, i, j);
	//printf("d_token:%s:\n", d_token);
	if (!d_token[1] || (d_token[1] == '"' && !d_token[2])
		|| (d_token[1] == '\'' && !d_token[2]))
	{
		free (d_token);
		return (0);
	}
	while (env_var)
	{
		substr = ft_strnstr(d_token, env_var->key, ft_strlen(d_token));
		if (substr != NULL)
		{
			if (wrong_var_form(token->str, i, env_var->key))
			{
				//printf("wrong var form\n");
				free(d_token);
				return (1);
			}
			free(d_token);
			return (0);
		}
		env_var = env_var->next;
	}
	free (d_token);
	return (1);
}

void	delete_invalid_var(t_token *token, int i)
{
	int	j;
	char 	*before;
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
	//printf("before:%s:\nafter:%s:\n", before, after);
	free(token->str);
	token->str = ft_strjoin(before, after);
	free(before);
	free(after);
}

//check if token contains $not_var or ${not_var} outside single quotes
//if it has invalid $, delete it
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
		}
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

int	var_key_len(char *token, int i, char *key)
{
	char	*valid_var;
	char	*valid_var_p;
	char	*token_substr;
	int	token_substrlen;

	token_substr = ft_substr(token, i, ft_strlen(key) + 1);
	token_substrlen = ft_strlen(token_substr);
	//printf("token_substrlen1: %d\n", token_substrlen);
	//printf("EXPAND token_substr:%s:\n", token_substr);
	valid_var = NULL;
	valid_var = ft_strjoin("$", key);
	if (!ft_strncmp(token_substr, valid_var, ft_strlen(valid_var)))
	{
		free(token_substr);
		free(valid_var);
		return (token_substrlen + i);
	}
	free(token_substr);
	free(valid_var);
	token_substr = ft_substr(token, i, ft_strlen(key) + 3);
	token_substrlen = ft_strlen(token_substr);
	//printf("token_substrlen: %d:\n", token_substrlen);
	valid_var_p = ft_strjoin(key, "}");
	valid_var = ft_strjoin("${", valid_var_p);
	//printf("valid var len2:%ld\n", ft_strlen(valid_var));
	if (!ft_strncmp(token_substr, valid_var, ft_strlen(valid_var)))
	{
		free(token_substr);
		free(valid_var);
		free(valid_var_p);
		return (token_substrlen + i);
	}
	//free(token_substr);
	//free(valid_var);
	//free(valid_var_p);
	return (1);
}

void	set_value(t_token *token, int i, char *value, char *key)
{
	int	j;
	char 	*before;
	char	*after;
	char	*var;

	/*j = i + 1;
	while (token->str[j] && token->str[j] != '$' && token->str[j] != '\''
			&& token->str[j] != '"' && token->str[j] != '}')
	{
		if (token->str[j] == '{')
		{
			while (token->str[j] != '}')
			{
				j++;
			}
			break ;
		}
		j++;
	}
	if (token->str[j] == '}')
		j++;
	*/
	j = var_key_len(token->str, i, key);
	//printf("j:%d\n", j);
	before = ft_substr(token->str, 0, i);
	//printf("token->str:%s:\n", token->str);
	after = ft_substr(token->str, j, ft_strlen(token->str));
	//printf("after:%s:\n", after);
	var = ft_strjoin(value, after);
	//printf("var:%s\n", var);
	free(token->str);
	token->str = ft_strjoin(before, var);
	free(before);
	free(after);
	free(var);
	//printf("posle expand:%s:\n", token->str);
}

void	expand_var(t_token *token, int i, t_env *env_var)
{
	int	j;
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
		{
			i++;
			while (token->str[i] != '"')
			{
				if (token->str[i] == '$')
				{
					if (contains_valid_var(token->str, i, env_var))
					{
						expand_var(token, i, env_var);
						i--;
					}
				}
				i++;
			}
		}
		if (token->str[i] == '$')
		{
			if (contains_valid_var(token->str, i, env_var))
			{
				expand_var(token, i, env_var);
				i--;
			}
		}
		i++;
	}
}

//Go through tokens, check if it contains a variable, check if variable is quoted
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
			//printf("main token:%s:\n", token->str);
			delete_invalid_dollar(token, env_struct);
			//printf("main token:%s:\n", token->str);
			if (token->str[0] != '\0')
				expand(token, env_struct);
		}
		if (token)
			token = token->next;
	}
	return (1);
}
