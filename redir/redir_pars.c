#include "../minishell.h"

//malloc les redirections pour toute les cmd
void	malloc_all(t_data *data)
{
	redirOrNot(data->cmdIndex);
	initRedirOrnot(data->cmdIndex);
	malloc_redir(data);
}


// decoupe les file des redirections
void	get_file(t_data *data)
{
	
}