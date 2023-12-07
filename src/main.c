/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:33:44 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/07 16:44:29 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_s;

	(void)argc;
	env_s = env_init(envp);
	ft_export(argv[1], env_s);
	ft_export(NULL, env_s);
	clear_env(env_s);
}
