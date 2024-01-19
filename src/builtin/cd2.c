/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:53:10 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/19 19:31:26 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_arg(t_env *env, char *path, char *oldpwd)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strcmp(path, ".."))
		tmp = ft_strjoin(path, "/");
	else
		tmp = ft_strdup(path);
	if (chdir(tmp) < 0)
	{
		perror("minishell: cd");
		free(tmp);
		if (oldpwd)
			free(oldpwd);
		return ;
	}
	else
	{
		set_oldpwd(env, oldpwd);
	}
	free(tmp);
}
