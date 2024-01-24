/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_executables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:10:48 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 08:23:30 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*#include <sys/stat.h>   // stat
#include <stdbool.h>    // bool type

bool file_exists (char *filename) {
  struct stat   buffer;
  return (stat (filename, &buffer) == 0);
}*/

void	set_executable(t_token *token)
{
	if (access(token->str+2, F_OK) == 0)
		token->type = COMMAND;
	//if (file_exists(token->str+2))
	//	token->type = COMMAND;
	//printf("jeste executable: %s\n", token->str);
}

int	check_executables(t_command *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (!ft_strcmp(token->str, "./"))
			set_executable(token);
		token = token->next;
	}
	return (1);
}
