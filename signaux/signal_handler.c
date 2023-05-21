/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:30 by vloth             #+#    #+#             */
/*   Updated: 2023/05/21 22:08:01 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void	newline(void);
void	sigint_handler(int sig);
void 	sigquit_handler(int sig);
void	signal_handler(void);
*/
//GESTION DES SIGNAUX

void	newline(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	newline();
	if (global.pid == 0)
		rl_redisplay();
}

void sigquit_handler(int sig)
{
	(void)sig;
	ft_putendl_fd("CTRL-D = Segmentation fault", 2);
	exit(128);
}

void	signal_handler(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, &sigquit_handler);
}