/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:27:00 by vloth             #+#    #+#             */
/*   Updated: 2023/09/07 05:37:05 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_here_doc_file(void)
{
	int	fd;

	fd = open(HERE_DOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (fd);
}

static char	*read_input_line(void)
{
	char	*line;

	line = readline("> ");
	return (line);
}

static void	write_line_to_file(int fd, const char *line)
{
	char	*mutable_line;

	mutable_line = strdup(line);
	ft_putstr_fd(mutable_line, fd);
	write(fd, "\n", 1);
	free(mutable_line);
}

static void	close_and_cleanup(int fd, char *line)
{
	if (line != NULL)
	{
		free(line);
	}
	close(fd);
}

void	ft_create_here_doc(char *delimiter)
{
	int		fd;
	char	*line;

	here_doc_signal();
	fd = open_here_doc_file();
	line = read_input_line();
	while (line != NULL)
	{
		if ((!strcmp(line, delimiter)))
		{
			free(line);
			break ;
		}
		write_line_to_file(fd, line);
		free(line);
		line = read_input_line();
	}
	close_and_cleanup(fd, NULL);
	connect_signal();
}
