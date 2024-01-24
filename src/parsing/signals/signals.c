/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:02:27 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/24 18:48:33 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hd_signal_handler(int sig)
{
	close(STDIN_FILENO);
	g_status = 128 + sig;
}

void	restore_signal(void)
{
	struct sigaction	siga;

	siga.sa_handler = SIG_DFL;
	sigemptyset(&siga.sa_mask);
	siga.sa_flags = 0;
	sigaction(SIGINT, &siga, NULL);
	sigaction(SIGQUIT, &siga, NULL);
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


void	ignor_signal(void)
{
	struct sigaction	siga;

	siga.sa_handler = SIG_IGN;
	sigemptyset(&siga.sa_mask);
	siga.sa_flags = 0;
	sigaction(SIGINT, &siga, NULL);
	sigaction(SIGQUIT, &siga, NULL);
}

void	sigint_handler(int sig)
{
	ft_dprintf(2, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 128 + sig;
}



void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
