/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:11 by vloth             #+#    #+#             */
/*   Updated: 2023/05/22 14:28:04 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//passe les espaces a parir des 2 caractere de cd
//et regarde si cest juste cd ou un cd /repertoir
int settings_cd(t_cmd *cmd)
{
	if (cmd->argv[1] == NULL)
		return (0);
	return (1);
}

//change les variables denv OLPWD et PWD et execute cd
// mais je vais devoir enlever quelques erreur possible
//genre si cest        cd /repertoire
void	ft_cd(t_cmd *cmd, t_envSom *env, t_data *data)
{
	char *path;
	char *olpwd = getcwd(NULL, 0);

	if (settings_cd(cmd) == 0)
		path = getenv("HOME");
	else
		path = cmd->argv[1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		data->exit_return = 1;
	}
	else
	{
		data->exit_return = 0;
		change_pwd(env);
		change_oldpwd(env, olpwd);
	}
}