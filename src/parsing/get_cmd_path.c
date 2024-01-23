/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:29:02 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/23 22:57:09 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_env *env_vars)
{
	char	*full_path;
	char	**full_path_split;

	full_path = NULL;
	while (env_vars)
	{
		if (!ft_strcmp("PATH", env_vars->key))
		{
			full_path = ft_strdup(env_vars->value);
		}
		env_vars = env_vars->next;
	}
	if (!full_path)
		return (NULL);
	full_path_split = ft_split(full_path, ':');
	free(full_path);
	return (full_path_split);
}

char	*path_exists(char **full_path_split, char *full_path, int i)
{
	if (!full_path_split || !full_path_split[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

char	*find_cmd_path(char **full_path_split, char *cmd)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	full_path = NULL;
	while (full_path_split && full_path_split[i])
	{
		free(full_path);
		tmp = ft_strjoin(full_path_split[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
		i++;
	}
	if (path_exists(full_path_split, full_path, i) == NULL)
		return (NULL);
	return (full_path);
}

char	*get_cmd_path(char *cmd, t_command *cmd_struct)
{
	char	**full_path_split;
	char	*path;

	path = NULL;
	full_path_split = get_path(cmd_struct->lst_env);
	if (!full_path_split)
		return (NULL);
	if (!is_builtin(cmd))
	{
		path = find_cmd_path(full_path_split, cmd);
	}
	free_split(full_path_split);
	return (path);
}
