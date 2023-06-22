#include "../minishell.h"

void	ft_create_here_doc(char *delimiter)
{
	int		fd;
	char	*buffer;

	buffer = NULL;
	fd = open(HERE_DOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	/* proper exit required in case of error ?! 
	if (fd == -1)
		printf("Heredoc fd err: '%d'\n", fd);
	*/
	write(1, "> ", 2);
	while (get_next_line(0, &buffer) > 0)
	{
		/* we need to handle the case of ctrl^C / ctrl^D */
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
