/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:05:14 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/18 17:13:42 by rtissera         ###   ########.fr       */
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

void	printpars(char *word)
{
	int		i;
	int		j;
	char	*var;
	char	*varenv;

	i = 1;
	while (word[i])
	{
		if (word[i] == '$')
		{
			j = 1;
			while (ft_isalpha(word[i + j]) || word[i + j] == '_')
				j++;
			var = malloc(sizeof(char) * j);
			var[j] = '\0';
			while (j--)
				var[j] = word[i + j];
			varenv = getenv(var);
			ft_putstr_fd(varenv, 1);
			i += j;
		}
		else
			ft_putchar_fd(word[i], 1);
		i++;
	}
}

void	echo(char **array)
{
	int	i;
	int	b;

	i = nnn(array, 1);
	b = 1;
	if (i != 0)
		b = 0;
	while (array[i])
	{
		printpars(array[i]);
		if (array[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (b)
		ft_putchar_fd('\n', 1);
}
