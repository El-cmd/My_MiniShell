/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:00 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:26:01 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void	ft_simple_pipe(t_cmdIndex *index, char **envp, t_envSom *env);
void	multi_pipe(t_cmdIndex *index, char **envp, t_envSom *env);
void	ft_multi_pipe(t_cmd *cmd, char **envp, t_envSom *env, int *status2);
void	ft_child(t_cmd *cmd, char **envp, t_envSom *env, int fd[2]);
void	ft_parent(int pid, int *status, int fd[2]);
*/
// execution d'un seul pipe et donc deux commandes
void ft_simple_pipe(t_cmdIndex *index, char **envp, t_envSom *env)
{
	pid_t pid;
	pid_t pid2;
	int fd[2];
	int status;

	if (index->nb_pipe == 1)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			pipe(fd);
			pid = fork_error();
			if (pid == 0)
				ft_child(index->begin, envp, env, fd);
			else
			{
				ft_parent(pid, &status, fd);
				if (ft_builtins(index->end, env) == 0)
					exit(0);
				ft_execve(index->end->cmd, envp);
			}
		}
		else
			waitpid(pid2, &status, 0);
	}
}

void multi_pipe(t_cmdIndex *index, char **envp, t_envSom *env)
{
	pid_t	pid;
	int		status;
	int		status2;
	t_cmd	*cmd;

	cmd = index->begin;
	pid = fork_error();
	if (pid == 0)
	{
		while (cmd)
		{
			ft_multi_pipe(cmd, envp, env, &status2);
			cmd = cmd->next;
		}
	}
	else
		waitpid(pid, &status, 0);
}

void	ft_multi_pipe(t_cmd *cmd, char **envp, t_envSom *env, int *status2)
{
	int		fd[2];
	pid_t	pid2;

	if (cmd->next != NULL)
		if (pipe(fd) == -1)
			exit(1);
	pid2 = fork_error();
	if (pid2 == 0)
		ft_child(cmd, envp, env, fd);
	else
	{
		if (cmd->next != NULL)
			ft_parent(pid2, status2, fd);
		else
		{
			ft_parent(pid2, status2, fd);
			if (ft_builtins(cmd, env) == 0)
				exit(0);
			ft_execve(cmd->cmd, envp);
		}
	}
}

void	ft_child(t_cmd *cmd, char **envp, t_envSom *env, int fd[2])
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	if (ft_builtins(cmd, env) == 0)
		exit(0);
	ft_execve(cmd->cmd, envp);
}

void	ft_parent(int pid, int *status, int fd[2])
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	waitpid(pid, status, 0);
}

/*
//execution de plus de deux commande mais quelques bug
void multi_pipe(t_cmdIndex *index, char **envp, t_envSom *env)
{
	pid_t	pid;
	int		fd[2];
	pid_t	pid2;
	int		status;
	int		status2;
	t_cmd	*cmd;

	cmd = index->begin;
	pid = fork_error();
	if (pid == 0)
	{
		while (cmd)
		{
			if (cmd->next != NULL)
			{
				if (pipe(fd) == -1)
					exit(1);
			}
			pid2 = fork_error();
			if (pid2 == 0)
			{
				close(fd[0]);
				dup2(fd[1], IN);
				close(fd[1]);
				if (ft_builtins(cmd, env) == 0)
					exit(0);
				ft_execve(cmd->cmd, envp);
			}
			else
			{
				if (cmd->next != NULL)
				{
					close(fd[1]);
					dup2(fd[0], OUT);
					close(fd[0]);
					close(fd[1]);
					waitpid(pid2, &status2, 0);
				}
				else
				{
					close(fd[1]);
					dup2(fd[0], OUT);
					close(fd[0]);
					waitpid(pid2, &status2, 0);
					if (ft_builtins(cmd, env) == 0)
						exit(0);
					ft_execve(cmd->cmd, envp);
				}
			}
			cmd = cmd->next;
		}
	}
	else
		waitpid(pid, &status, 0);
}

void ft_simple_pipe(t_cmdIndex *index, char **envp, t_envSom *env)
{
	pid_t pid;
	pid_t pid2;
	int fd[2];
	int status;

	if (index->nb_pipe == 1)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			pipe(fd);
			pid = fork_error();
			if (pid == 0)
			{
				close(fd[0]);
				dup2(fd[1], IN);
				close(fd[1]);
				if (ft_builtins(index->begin, env) == 0)
					exit(0);
				ft_execve(index->begin->cmd, envp);
			}
			else
			{
				close(fd[1]);
				dup2(fd[0], OUT);
				close(fd[0]);
				waitpid(pid, &status, 0);
				if (ft_builtins(index->end, env) == 0)
					exit(0);
				ft_execve(index->end->cmd, envp);
			}
		}
		else
			waitpid(pid2, &status, 0);
	}
}
*/
