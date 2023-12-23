/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:15:28 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/23 10:30:29 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path, t_env *env)
{
	if (!path)
	{
		while (env)
		{
			if (chdir(getenv("HOME")))
			{
				if (chdir(env->value))
					perror("bash: cd");
			}
		}
		if (!env)
			printf("bash: cd: HOME not set\n");
		// if (chdir(getenv("HOME")))
		// 	perror("cd");
	}
	else if (!ft_strncmp(path, "-", 1))
	{
		if (chdir(getenv("OLDPWD")))
			printf("bash: cd: OLDPWD not set\n");
		else
			printf("%s\n", getenv("OLDPWD"));
	}
	else if (chdir(path))
		perror("bash: cd");
}
