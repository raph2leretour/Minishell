/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:05:14 by rtissera          #+#    #+#             */
/*   Updated: 2023/11/13 19:07:03 by rtissera         ###   ########.fr       */
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

int	dollar(char **array, int i)
{
	int	j;
	char	*var;

	j = 0;
	if (array[i][0] != "(")
	{
		var = getenv(array[i][0]);
		if (var)
			printf("%s", var);
	}
}

void	echo(char **array)
{
	int	i;

	i = nnn(array, 0);
	if (i != 0)
	{
		while (array[i])
		{
			printf("%s", array[i]);
			if (array[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else
	{
		while (array[i])
		{
			printf("%s", array[i]);
			if (array[i + 1])
				printf(" ");
			i++;
		}
	}
}
/*
int	main(int ac, char **av)
{
	int	i;
	char	**array;

	if (ac > 1)
	{
		array = malloc(sizeof(char *) * ac);
		array[ac - 1] = NULL;
		i = 0;
		while (av[i + 1])
		{
			array[i] = malloc(sizeof(char) * (strlen(av[i + 1] + 1)));
			strcpy(array[i], av[i + 1]);
			i++;
		}
		echo(array);
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	return (0);
}*/
