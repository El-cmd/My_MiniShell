/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:27:00 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 16:27:01 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_create_here_doc(char *delimiter)
{
	int		fd;
	char	*buffer;

	buffer = NULL;
	fd = open(HERE_DOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(1, "> ", 2);
	while (get_next_line(0, &buffer) > 0)
	{
		if (!ft_strncmp(buffer, delimiter, ft_strlen(buffer)))
			break ;
		else
		{
			ft_putstr_fd(buffer, fd);
			write(fd, "\n", 1);
		}
		free(buffer);
		write(1, "> ", 2);
	}
	free(buffer);
	close (fd);
}
