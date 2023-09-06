/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd_suite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldoctor <eldoctor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:51:35 by vloth             #+#    #+#             */
/*   Updated: 2023/09/06 14:35:52 by eldoctor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error(char *line)
{
	int	pipe_error;

	pipe_error = 0;
	if (no_str(line) == 1 || others_char(line))
	{
		free(line);
		return (-1);
	}
	line = debug(line);
	pipe_error = check_error(line);
	return (pipe_error);
}

int	pipe_quote(char *line, t_cmd_index *index)
{
	if (!split_quotes(line, index))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	pipe_cut(char *line, t_cmd_index *index)
{
	if (splitage(line, index))
	{
		free(line);
		return (1);
	}
	return (0);
}

void	not_pipe(char *line, t_cmd_index *cmd_index)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " ");
	pushback_cmd(trimmed_line, cmd_index, check_quotes(line));
	free(trimmed_line);
}
