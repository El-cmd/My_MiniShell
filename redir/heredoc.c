#include "../minishell.h"

/* malloc.. **delim need to be freed 
static void	get_here_doc_delimiters(t_cmd *cmd, t_redir *redir)
{
	int		i;

	cmd->here.delim = NULL;
	redir = cmd->lredir->begin;
	cmd->here.num = 0;
	while (redir)
	{
		if (redir->type == HERD)
			cmd->here.num++;
		redir = redir->next;
	}
	if (cmd->here.num == 0)
		return ;
	cmd->here.delim = (char **)malloc(sizeof(char *) * (cmd->here.num + 1));
	if (!cmd->here.delim)
		return ;
	redir = cmd->lredir->begin;
	i = -1;
	while (redir)
	{
		if (redir->type == HERD)
			cmd->here.delim[++i] = ft_strdup(redir->file);
		redir = redir->next;
	}
	cmd->here.delim[++i] = NULL;
}
*/

/*
static void	ft_free_delimiters(char **str)
{
	int	i;

	i = -1;
	if (**str)
	{
		while (str[++i])
			free(str[i]);
		free(str);
	}
}

static int	number_of_delimiters(t_redir *redir)
{
	int	count;

	count = 0;
	while (redir)
	{
		if (redir->type == HERD)
			count++;
		redir = redir->next;
	}
	return (count);
}
*/

/* here_doc works fine as it is ! 
** however, it is necessary to quit properly in case of ctrl^C !! */
static void	ft_create_here_doc(char *delimiter)
{
	int		fd;
	char	*buffer;

	buffer = NULL;
	fd = open(HERE_DOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
	}
	free(buffer);
	close(fd);
}

void	ft_here_doc(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->lredir->begin;
	while (redir)
	{
		if (redir->type == HERD)
			ft_create_here_doc(redir->file);
		redir = redir->next;
	}
}
