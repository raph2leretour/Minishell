/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:36:16 by smilosav          #+#    #+#             */
/*   Updated: 2023/10/31 20:37:55 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/include/libft.h"
#include "lexer.h"

char	**tokenize(char *command)
{
	char	**tokens;

	command = ft_strtrim(command, " \t\r\v\f\n");
	tokens = ft_split(command, ' ');
	return (tokens);
}
