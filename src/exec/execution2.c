/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 05:26:21 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/25 05:29:28 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_error_handler(t_command *t_cmd, t_simple_cmd *t_scmd, \
		char **c_env, char **s_cmd)
{
	ft_dprintf(2, "%s: %s\n", t_scmd->first_token->str, strerror(errno));
	free_exit(t_cmd, c_env, s_cmd, 126);
}
