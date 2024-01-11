/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:05:14 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/10 16:17:50 by rtissera         ###   ########.fr       */
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
	return (1);
}

void	printpars(char *word, t_env *env)
{
	int		i;
	char	*var;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
		{
			var = ft_getenv(word + i + 1, env);
			ft_putstr_fd(var, 1);
			return ;
		}
		else
			ft_putchar_fd(word[i], 1);
		i++;
	}
}

void	echo(char **array, t_env *env)
{
	int	i;
	int	b;

	i = nnn(array, 1);
	b = 1;
	if (i > 1)
		b = 0;
	while (array[i])
	{
		printpars(array[i], env);
		if (array[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (b)
		ft_putchar_fd('\n', 1);
	free_array(array);
}
