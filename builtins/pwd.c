/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:34 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:26:35 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//affiche le repertoir courrant
int	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	data->exit_return = 0;
	return (0);
}