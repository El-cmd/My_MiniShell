/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:30 by vloth             #+#    #+#             */
/*   Updated: 2023/09/07 20:14:32 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	connect_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	abort_handler(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
}

void	ft_signalhd(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		close(0);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	cmdbloc_signal(void)
{
	signal(SIGINT, del_handler);
	signal(SIGQUIT, abort_handler);
}

void	here_doc_signal(void)
{
	signal(SIGINT, ft_signalhd);
	signal(SIGQUIT, ft_signalhd);
}
