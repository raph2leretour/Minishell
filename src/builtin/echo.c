/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:05:14 by rtissera          #+#    #+#             */
/*   Updated: 2023/11/03 13:22:08 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../../inc/minishell.h"

void	echo(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		if (array[i][j] && array[i][j] == '-')
		{
			while (array[i][j] && array[i][j] == 'n')
				j++;
		}
		else
			break ;
		if (array[i][j])
			break ;
		i++;
	}
	if (i > 0)
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
