#include "../minishell.h"

/*
int		ft_pipeError(char *line);
void	splitage(char *line, t_cmdIndex *cmdIndex);
void	splitOrNot(char *line, t_cmdIndex *cmdIndex);
*/
// regarde sil y a des pipe ou non
//et aussi si il y a des || ou des pipe invalide genre 
// ls | grep truc | \0
int	ft_pipeError(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
				return (1);
			if (line[i + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	if (j > 0)
		return (0);
	return (2);
}


//split le buffer par rapport au pipe et enleve les espace
//au debut et a la fin de chaque commande
//et enfin les ajoute dans la liste chainé
void	splitage(char *line, t_cmdIndex *cmdIndex)
{
	char	**line_second;
	int i;

	i = 0;
	//toujours ne pas oublier les leaks et d'opti split
	line_second = ft_split(line, '|');
	while (line_second[i])
	{
		line_second[i] = ft_strtrim(line_second[i], " ");
		i++;
	}
	i = 0;
	while (line_second[i])
	{
		pushback_cmd(line_second[i], cmdIndex);
		i++;
	}
}

// par rapport a la commande regarde sil doit split ou pas
void	splitOrNot(char *line, t_cmdIndex *cmdIndex)
{
	if (ft_pipeError(line) == 1)
		return ;
	else if (ft_pipeError(line) == 2)
		pushback_cmd(line, cmdIndex);
	else if (ft_pipeError(line) == 0)
		splitage(line, cmdIndex);
}

void find_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->redir == false)
		return ;
	else 
	{
		while (cmd->cmd[i])
		{
			pass_space(cmd->cmd, &i);
			if (is_redir_or_cmd(cmd->cmd[i]))
			{
				i++;
				if (is_redir_or_cmd(cmd->cmd[i]))
				{
					i++;
					pass_space(cmd->cmd, &i);
					get_file(cmd->cmd, &i);
					pass_space(cmd->cmd, &i);
					i--;
					if (is_redir_or_cmd(cmd->cmd[i] == 0))
					{
						cut(cmd, &i);
						return;
					}
				}
				else
				{
					pass_space(cmd->cmd, &i);
					get_file(cmd->cmd, &i);
					pass_space(cmd->cmd, &i);
					i--;
					if (is_redir_or_cmd(cmd->cmd[i] == 0))
					{
						cut(cmd, &i);
						return ;
					}
				}
			}
			else
			{
				cut(cmd, &i);
				return ;
			}
			i++;
		}
	}
}

void exec_find_cmd(t_data *data)
{
	t_cmd *tmp;

	tmp = data->cmdIndex->begin;
	while (tmp)
	{
		find_cmd(tmp);
		tmp = tmp->next;
	}
}