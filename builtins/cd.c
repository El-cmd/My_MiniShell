/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:11 by vloth             #+#    #+#             */
/*   Updated: 2023/09/03 15:10:21 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//passe les espaces a parir des 2 caractere de cd
//et regarde si cest juste cd ou un cd /repertoir
int	settings_cd(t_cmd *cmd)
{
	if (cmd->argv[1] == NULL)
		return (0);
	return (1);
}

//change les variables denv OLPWD et PWD et execute cd
// mais je vais devoir enlever quelques erreur possible
//genre si cest        cd /repertoire

// Fonction pour changer le répertoire de travail actuel (cd)
void	change_directory(char *path, t_env_som *env, t_data *data)
{
	char	*olpwd;

	olpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		free(olpwd);
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		data->exit_return = 1;
	}
	else
	{
		data->exit_return = 0;
		change_pwd(env);
		change_oldpwd(env, olpwd);
		free(olpwd);
	}
}

// Fonction principale ft_cd
void	ft_cd(t_cmd *cmd, t_env_som *env, t_data *data)
{
	char	*path;
	int		i;

	i = 0;
	while (cmd->argv[i])
		i++;
	if (i >= 3)
	{
		ft_putstr_fd("Error: 3 arguments\n", 2);
		return ;
	}
	if (settings_cd(cmd) == 0)
		path = getenv("HOME");
	else
		path = cmd->argv[1];
	change_directory(path, env, data);
}
