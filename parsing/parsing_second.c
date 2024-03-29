/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:10:02 by eldoctor          #+#    #+#             */
/*   Updated: 2023/09/07 16:43:51 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fait_le_cafe_second(char **test, int j)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strtrim(test[j], "\"");
	free(test[j]);
	test[j] = ft_strdup(tmp);
	free(tmp);
}

void	do_meta_second(t_data *data, int i, t_cmd *cmd)
{
	char	**test;
	char	*tmp;

	tmp = ft_strtrim(cmd->argv[i], "\"");
	free(cmd->argv[i]);
	cmd->argv[i] = ft_strdup(tmp);
	free(tmp);
	test = ft_split_squote(cmd->argv[i], '$');
	free(cmd->argv[i]);
	cmd->argv[i] = fait_le_cafe(test, data);
	free_tab(test);
}
