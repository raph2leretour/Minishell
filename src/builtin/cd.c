/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:15:28 by rtissera          #+#    #+#             */
/*   Updated: 2023/11/11 11:25:20 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path)
{
	if (!path)
	{
		if (chdir("~"))
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
