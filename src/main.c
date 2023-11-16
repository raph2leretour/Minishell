/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:33:44 by rtissera          #+#    #+#             */
/*   Updated: 2023/11/16 16:49:45 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	int	i;
	char	**array;

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
	return (0);
}
