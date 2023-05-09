#include "../minishell.h"

//malloc les redirections pour toute les cmd
void	malloc_all(t_data *data)
{
	redirOrNot(data->cmdIndex);
	initRedirOrnot(data->cmdIndex);
	malloc_redir(data);
}


//en construction ---------------->>>>>>>
// decoupe les file des redirections
//void	get_file_redir(t_data *data)
//{
//	int i;
//
//	i = 0;
//	t_cmd *tmp;
//	t_redir *redir;
//	redir = tmp->lredir->begin;
//	tmp = data->cmdIndex->begin;
//	while (tmp->cmd[i])
//	{
//		if (tmp->cmd[i] == '<')
//		{
//			i++;
//			if (tmp->cmd[i] == '<')
//			{
//				i++;
//				pass_space(tmp->cmd, i);
//				//ici mettre le substr
//				get_file(tmp->cmd, i);
//			}
//			else
//			{
//				pass_space(tmp->cmd, i);
//				get_file(tmp->cmd, i);
//			}
//		}
//		i++;
//	}
//	return (0);
//}