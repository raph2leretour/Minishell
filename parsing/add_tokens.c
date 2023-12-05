/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:32:38 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/05 18:44:32 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/include/libft.h"
#include "lexer.h"

int	add_token_redirection(t_command *cmd_struct, int i)
{
	int		j;
	int		len;
	char	*cmd;
	t_token	*new_token;

	j = i;
	len = 0;
	while (cmd_struct->string[i] && is_redirection(cmd_struct->string[i]))
	{
		i++;
		len++;
	}
	cmd = ft_substr(cmd_struct->string, j, len);
	new_token = init_token(cmd, REDIRECTION);
	add_token(&cmd_struct->first_token, new_token);
	return (i);
}

int	add_token_parenthesis(t_command *cmd_struct, int i)
{
	int		j;
	int		len;
	char	*cmd;
	t_token	*new_token;

	j = i;
	len = 0;
	while (cmd_struct->string[i] && is_parenthesis(cmd_struct->string[i]))
	{
		i++;
		len++;
	}
	cmd = ft_substr(cmd_struct->string, j, len);
	new_token = init_token(cmd, PARENTHESIS);
	add_token(&cmd_struct->first_token, new_token);
	return (i);
}

int	add_token_pipe(t_command *cmd_struct, int i)
{
	int		j;
	int		len;
	char	*cmd;
	t_token	*new_token;

	j = i;
	len = 0;
	while (cmd_struct->string[i] && cmd_struct->string[i] == '|')
	{
		i++;
		len++;
	}
	cmd = ft_substr(cmd_struct->string, j, len);
	new_token = init_token(cmd, PIPE);
	add_token(&cmd_struct->first_token, new_token);
	return (i);
}

int	add_token_and(t_command *cmd_struct, int i)
{
	int		j;
	int		len;
	char	*cmd;
	t_token	*new_token;

	j = i;
	len = 0;
	while (cmd_struct->string[i] && cmd_struct->string[i] == '&')
	{
		i++;
		len++;
	}
	cmd = ft_substr(cmd_struct->string, j, len);
	new_token = init_token(cmd, AND);
	add_token(&cmd_struct->first_token, new_token);
	return (i);
}

int	add_token_semi(t_command *cmd_struct, int i)
{
	int		j;
	int		len;
	char	*cmd;
	t_token	*new_token;

	j = i;
	len = 0;
	while (cmd_struct->string[i] && cmd_struct->string[i] == ';')
	{
		i++;
		len++;
	}
	cmd = ft_substr(cmd_struct->string, j, len);
	new_token = init_token(cmd, SEMI);
	add_token(&cmd_struct->first_token, new_token);
	return (i);
}
