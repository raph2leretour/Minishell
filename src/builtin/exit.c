/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:43:09 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/20 18:48:35 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Ne pas oublier de tout free
 * Les signals...
 */
void	ft_exit(char *strn)
{
	int	i;

	if (strn && strn[0])
	{
		i = 0;
		while (strn[i])
		{
			if (!ft_isdigit(strn[i]))
				exit(2);
			i++;
		}
		errno = ft_atoi(strn);
		exit(errno);
	}
	else
		exit(0);
}
