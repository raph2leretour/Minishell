/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:49:51 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/26 18:35:17 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *s, int errnum)
{
	ft_putstr_fd(s, 2);
	ft_putchar_fd('\n', 2);
	// printf("%s\n", s);
	errno = errnum;
}
