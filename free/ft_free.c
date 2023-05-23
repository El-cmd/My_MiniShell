/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:38 by vloth             #+#    #+#             */
/*   Updated: 2023/05/23 06:30:05 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
t_cmd 	*pop_front_dlist(t_cmdIndex *index);
void	free_list(t_cmdIndex *index);
void	free_tab(char **str);

t_cmd *pop_front_dlist(t_cmdIndex *index)
{
	t_cmd *tmp;

	tmp = index->begin;
	if (index->nb_cmd == 1)
	{
		free(tmp->cmd);
		index->begin = NULL;
		index->end = NULL;
	}
	else
	{
		free(tmp->cmd);
		index->begin = index->begin->next;
		index->begin->back = NULL;
	}
	index->nb_cmd--;
	return (tmp);
}

void	free_list(t_cmdIndex *index)
{
	t_cmd	*tmp;

	tmp = index->begin;
	while (tmp)
	{
		tmp = pop_front_dlist(index);
		free(tmp);
	}
	free(index);
	index = NULL;
}
*/

void	free_tab(char **str)
{
	int i;

	i = -1;
	if (str)
	{
		while (str[++i])
			free(str[i]);
		free(str);
	}
	//str = NULL;
}

void	ft_free_cmd(t_cmd *cmd, t_redir *redir)
{
	t_redir	*r_tmp;
	t_cmd	*tmp_cmd;

	while (cmd)
	{
		while (redir)
		{
			if (redir->file)
				free(redir->file);
			r_tmp = redir->next;
			free(redir);
			redir = NULL;
			redir = r_tmp;
		}
		free_tab(cmd->argv);
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->just_cmd)
			free(cmd->just_cmd);
		tmp_cmd = cmd->next;
		free(cmd);
		cmd = NULL;
		cmd = tmp_cmd;
	}
}

void	ft_free_env(t_envSom *env_som)
{
	t_env	*env;
	t_env	*tmp;
	
	env = env_som->begin;
	while (env)
	{
		if (env->name)
			free(env->name);
		tmp = env->next;
		free(env);
		env = NULL;
		env = tmp;
	}
	if (env_som)
		free(env_som);
}

void	ft_free_all_memory(t_data *data)
{
	t_envSom	*env_som;
	t_cmdIndex	*cmd_index;
	char		**path;

	env_som = data->env;
	ft_free_env(env_som);
	cmd_index = data->cmdIndex;
	ft_free_cmd(cmd_index->begin, cmd_index->begin->lredir->begin);
	if (cmd_index)
		free(cmd_index);
	path = data->path_exec;
	free_tab(path);
}
