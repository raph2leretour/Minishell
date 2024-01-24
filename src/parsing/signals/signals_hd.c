/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:26:55 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/24 20:27:30 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hd_signal_handler(int sig)
{
	close(STDIN_FILENO);
	g_status = 128 + sig;
}

void	hd_signal_mode(void)
{
	struct sigaction	siga;

	siga.sa_handler = hd_signal_handler;
	sigemptyset(&siga.sa_mask);
	siga.sa_flags = 0;
	sigaction(SIGINT, &siga, NULL);
	siga.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &siga, NULL);
}
