/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:15:28 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/17 18:11:58 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	cd(char *path)
{
	if (!path)
	{
		if (chdir(getenv("HOME")))
			perror("cd");
	}
	else if (!ft_strncmp(path, "-", 2))
	{
		if (chdir(getenv("OLDPWD")))
			perror("cd");
	}
	else if (chdir(path))
		perror("cd");
}
