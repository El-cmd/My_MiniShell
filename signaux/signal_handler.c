/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldoctor <eldoctor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:30 by vloth             #+#    #+#             */
/*   Updated: 2023/09/06 21:41:26 by eldoctor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	newline(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(void)
{
	signal(SIGABRT, &sig_sbrt);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, sigquit_handler);
	signal(SIGTSTP, SIG_IGN);
}

void	reset_signal_handlers(void)
{
	signal(SIGABRT, &sig_sbrt);
	signal(SIGINT, sigint_handler_cmd);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}
