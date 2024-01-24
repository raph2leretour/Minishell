/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:29:02 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 20:13:36 by smilosav         ###   ########.fr       */
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

int	found_path_is_valid(char *full_path, char *cmd)
{
	if (access(full_path, F_OK) == 0
		&& ft_strnstr(full_path, cmd, ft_strlen(full_path)))
		return (1);
	return (0);
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
		if (found_path_is_valid(full_path, cmd))
			break ;
		i++;
	}
	if (path_exists(full_path_split, full_path, i) == NULL)
		return (NULL);
	return (full_path);
}

char	*get_cmd_path(t_token *token, t_command *cmd_struct)
{
	char	**full_path_split;
	char	*path;
	char	*cmd;

	cmd = token->str;
	if (cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (NULL);
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
