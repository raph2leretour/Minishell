/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:33:44 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/08 17:24:32 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**a;
	t_env	*env_s;

	(void)argc;
	env_s = env_init(envp);
	ft_export(argv[1], env_s);
	ft_export(NULL, env_s);
	a = ft_split(argv[1], '=');
	unset(a[0], env_s);
	clear_env(env_s);
}
