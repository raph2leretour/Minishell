/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:05:14 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/21 11:46:53 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nnn(char **array, int i)
{
	int	j;

	while (array[i])
	{
		if (array[i][0] && array[i][0] == '-')
		{
			j = 1;
			while (array[i][j] && array[i][j] == 'n')
				j++;
			if (array[i][j])
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	echo(char **array, t_env *env)
{
	int	i;
	int	b;

	(void)env;
	i = nnn(array, 1);
	b = 1;
	if (i > 1)
		b = 0;
	while (array[i])
	{
		ft_dprintf(1, "%s", array[i]);
		if (array[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (b)
		ft_putchar_fd('\n', 1);
	free_array(array);
	return (0);
}
