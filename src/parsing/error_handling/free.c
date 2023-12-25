/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:11:42 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/25 22:50:48 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_tokens(t_token *first_token)
{
	t_token	*tmp;

	while (first_token)
	{
		tmp = first_token->next;
		free(first_token->str);
		free(first_token);
		first_token = tmp;
	}
	free(first_token);
}

void	free_simple_cmd_tokens(t_token *first_token)
{
	t_token *tmp;

	while (first_token)
	{
		tmp = first_token->next;
		free(first_token);
		first_token = tmp;
	}
	free(first_token);
}
void	free_simple_cmds(t_simple_cmd *first_cmd)
{
	t_simple_cmd	*tmp;

	while (first_cmd)
	{
		tmp = first_cmd->next;
		free(first_cmd->full_path);
		free_simple_cmd_tokens(first_cmd->first_token);
		free(first_cmd);
		first_cmd = tmp;
	}
	free(first_cmd);
}

void	free_env_vars(t_env *env_var)
{
	t_env	*tmp;

	while (env_var)
	{
		tmp = env_var->next;
		free(env_var->key);
		free(env_var->value);	
		free(env_var);
		env_var = tmp;
	}
	free(env_var);
}

void	free_cmd(t_command *cmd)
{
	if (cmd->first_token)
		free_tokens(cmd->first_token);
	if (cmd->first_cmd)
		free_simple_cmds(cmd->first_cmd);
	free(cmd);
}
