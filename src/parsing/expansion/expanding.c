/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:34:12 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/25 22:53:29 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

/*void	expanding(t_command *cmd_struct)
{
	t_token	*token;

	token = cmd_struct->first_token;
}*/
void	check_if_variable_valid(char *token, t_env *env_var)
{
	//int		variable_len;
	char	*sub_str;
	//char	*variable_value;

	sub_str = NULL;
	//variable_value = NULL;
	//variable_len = 0;
	while (env_var)
	{
		sub_str = ft_strnstr(token, env_var->key, ft_strlen(token));
		if (sub_str != NULL)
		{
			printf("Ima validna varijabla :%s\n", sub_str);
			//variable_len = ft_strlcpy(variable_value, 
					//env_var->key, ft_strlen(env_var->key));
			//printf("Pronadjena var velicine: %d\n", variable_len);
		}
		env_var = env_var->next;
	}
}

int	expanding(t_command *cmd_struct)
{
	t_env				*env_struct;
	t_token				*token;

	env_struct = cmd_struct->lst_env;
	token = cmd_struct->first_token;
	while (token)
	{
		check_if_variable_valid(token->str, env_struct);
		token = token->next;
	}
	return (1);	
}
