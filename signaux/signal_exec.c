/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldoctor <eldoctor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:49:39 by nspeciel          #+#    #+#             */
/*   Updated: 2023/09/06 21:40:15 by eldoctor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hd_on_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(128);
}

void	sigint_heredoc_handler(void)
{
	signal(SIGINT, hd_on_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_sbrt(int code)
{
	(void) code;
	write(1, "aborttest\n", 6);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	newline();
	if (g_global.pid == 0)
		rl_redisplay();
}

void	sigint_handler_cmd(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_global.pid == 0)
		rl_redisplay();
}

void	sigquit_handler(int sig)
{
	(void)sig;
	ft_putendl_fd("Segmentation fault", 2);
	exit(128);
}
