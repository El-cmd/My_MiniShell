#include "../minishell.h"

/* 
typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**paths;
	int		prev_fd;
	int		pipe_fd[2];
	int		num_commans;
	int		active_cmds;
	char	**commands;
	int		heredoc_fd;
}	t_pipex;
*/

void	ft_multiple_pipes(t_cmdIndex *index, char **envp);
void	ft_init_pipex(t_pipex **pipex);

void ft_pipex(t_cmdIndex *index, char **envp, t_envSom *env)
{
	t_env	*en;
	t_cmd	*cmd;
	t_redir	*rdr;
	int		i;

	en = env->begin;
	cmd = index->begin;
	printf("ft_pipex\n");
	printf("\tt_cmdIndex:\tnb_cmd:'%d'\tnb_pipes:'%d'\n", index->nb_cmd, index->nb_pipe);
	while (cmd)
	{
		printf("\tt_cmd\n\t\tcmd:'%s', redir:'%d'\tcmd @ '%p'\n", cmd->cmd, cmd->redir, cmd);
		if (cmd->redir)
		{
			rdr = cmd->lredir->begin;
			while (rdr)
			{
				printf("\t\tredir:\ttype:'%d', fd:'%d', begin:'%d', len:'%d', file:'%s'\n", rdr->type, rdr->fd, rdr->begin, rdr->len, rdr->file);
				rdr = rdr->next;
			}
		}
		cmd = cmd->next;
	}
	/* here each t_env node (en) holds a line from environment variables env */
	printf("\tt_envSom\tsize'%d':\n", env->size);
	while (en)
	{
		if (ft_strncmp(en->name, "PATH=", 5) == 0)
			printf("env name:\n'%s'\n", en->name);
		en = en->next;
	}
	/* here envp holds every directory in PATH env variable, separated by ':' */
	printf("\tchar **envp. PATH:\n");
	i = -1;
	while (envp[++i])
		printf("\t\tenvp:'%s'\n", envp[i]);
	printf("== == == == == ==\n");
	
	ft_multiple_pipes(index, envp);
}

void	ft_multiple_pipes(t_cmdIndex *index, char **envp)
{
	t_pipex	*pipex;
	int		i;

	pipex = NULL;
	ft_init_pipex(&pipex);
	ft_preprocess(index);
	//ft_preprocess(argc, argv, env, pipex);
	i = 0;
	while (i < my_data->num_commands)
	{
		ft_prepare_pipes(argc, argv, my_data, i);
		if (ft_check_condition_to_execute(my_data) == 1)
		{
			ft_exec_command(my_data, my_data->commands[i]);
			my_data->active_cmds++;
		}
		i++;
	}
	ft_wait_for_child_processes(pipex);
	ft_clean_full(pipex);
	return (0);
}

void	ft_init_pipex(t_pipex **pipex)
{
	t_pipex	*tmp;

	tmp = (t_pipex *)malloc(sizeof(t_pipex));
	tmp->infile = NULL;
	tmp->outfile = NULL;
	tmp->paths = NULL;
	tmp->prev_fd = -1;
	tmp->pipe_fd[0] = -1;
	tmp->pipe_fd[1] = -1;
	tmp->num_commans = -1;
	tmp->active_cmds = 0;
	tmp->commands = NULL;
	tmp->heredoc_fd = -1;
	*pipex = tmp;
}

void	ft_preprocess(t_pipex *pipex, t_cmdIndex *index)
{
	ft_preprocess_cmds(pipex, index);
	//ft_preprocess_get_allpaths();
}

void	ft_preprocess_cmds(t_pipex *pipex, t_cmdIndex *index)
{
	char	**commands;
	t_cmd	*cmd;
	int		i;

	cmd = index->begin;
	commands = (char **)malloc(sizeof(char *) * (index->nb_cmd + 1));
	// need to free properly in case of error
	if (!commands)
		ft_error_clean_exit(pipex);
	i = -1;
	while (++i < index->nb_cmd)
		commands[i] = cmd->cmd;
	commands[i] = NULL;
	pipex->commands = commands;
	pipex->num_commans = i;
}