#include "../minishell.h"

/*
void exec(t_cmdIndex *cmd, char **envp, t_envSom *envp_nodes);
void ft_execve(char *cmd, char **envp);
*/
// fonction d'execution
void ft_execve(char *cmd, char **envp)
{
	char **cmdarg;
	int y;
	char *exec;

	no_str(cmd);
	y = 0;
	cmdarg = ft_split(cmd, ' ');
	while (envp[++y])
	{
		exec = ft_strjoin(ft_strjoin(envp[y], "/"), cmdarg[0]);
		execve(exec, cmdarg, envp);
		free(exec);
	}
	ft_putstr_fd(cmdarg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_tab(cmdarg);
	exit(127);
}

//regarde quel execution faire si une ou plusieur cmd
//void exec(t_cmdIndex *cmd, char **envp, t_envSom *envp_nodes)
void exec(t_data *data)
{
	t_cmdIndex *index;
	char **path_dirs;
	t_envSom *envp_nodes;
	t_cmd *cmd;

	index = data->cmdIndex;
	path_dirs = data->path_exec;
	envp_nodes = data->env;
	cmd = index->begin;
	if (index->begin->redir == true)
		return ;
	if (index->nb_cmd == 1)
		simple_cmd(envp_nodes, cmd, path_dirs, index);
	else if (index->nb_cmd == 2)
		ft_simple_pipe(index, path_dirs, envp_nodes);
	else if (index->nb_cmd > 2)
	 	ft_pipex(data);
	 	//ft_pipex(index, path_dirs, envp_nodes);
		//multi_pipe(index, path_dirs, envp_nodes);
}