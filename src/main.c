/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:33:44 by rtissera          #+#    #+#             */
/*   Updated: 2023/11/28 18:34:15 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*env_s;

	(void)ac;
	env_s = env_init(env);
	ft_export(av[1], env_s);
	ft_export(NULL, env_s);
	clear_env(env_s);
}
