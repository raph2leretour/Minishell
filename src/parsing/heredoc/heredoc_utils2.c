/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:18:36 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 09:18:57 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*nbr;

	nbr = ft_itoa(i);
	if (!nbr)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, nbr);
	free(nbr);
	i++;
	return (name);
}

char	*set_value_heredoc(char *line, int i, char *value, char *key)
{
	int		j;
	char	*before;
	char	*after;
	char	*var;

	j = var_key_len(line, i, key);
	before = ft_substr(line, 0, i);
	after = ft_substr(line, j, ft_strlen(line));
	var = ft_strjoin(value, after);
	free(line);
	line = ft_strjoin(before, var);
	free(before);
	free(after);
	free(var);
	return (line);
}
