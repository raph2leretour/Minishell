/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:54:14 by smilosav          #+#    #+#             */
/*   Updated: 2023/10/31 20:51:35 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "lexer.h"

int	main(void)
{
	char	*str;
	char	**tokens;
	int	i;

	i = 0;
	while (1)
	{	
		str = readline("minishell$ ");
		//add_history(str);
		//printf("%s\n", str);
		tokens = tokenize(str);
		//free(str);
		while (tokens[i] != 0)
		{
			printf("%s\n", tokens[i]);
			i++;
		}
	}
	return (0);
}

