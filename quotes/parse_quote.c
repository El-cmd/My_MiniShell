/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:11:54 by vloth             #+#    #+#             */
/*   Updated: 2023/09/03 22:47:13 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_many_cmd(const char *str)
{
	int	count;
	int	in_quotes;
	int	i;

	count = 1;
	in_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			in_quotes = !in_quotes;
		if (str[i] == '|' && !in_quotes)
			count++;
		i++;
	}
	return (count);
}

// Fonction pour extraire et découper une commande
char	*extract_and_trim_cmd(const char *str, int start, int end)
{
	int		j;
	int		i;
	char	*cmd;
	char	*trimmed_cmd;

	j = 0;
	cmd = malloc(end - start + 2);
	if (!cmd)
	{
		perror("malloc");
		exit(1);
	}
	i = start;
	while (i <= end)
		cmd[j++] = str[i++];
	cmd[j] = '\0';
	trimmed_cmd = strdup(cmd);
	free(cmd);
	return (trimmed_cmd);
}

// Fonction pour diviser la chaîne en commandes
void	process_split(t_cmd_index *cmdI, const char *str, t_split *context)
{
	char	*cmd;

	while (str[context->i])
	{
		if (str[context->i] == '"' || str[context->i] == '\'')
			context->in_quotes = !(context->in_quotes);
		if (str[context->i] == '|' && !(context->in_quotes))
		{
			cmd = extract_and_trim_cmd(str, context->start, context->i - 1);
			pushback_cmd(cmd, cmdI, 0);
			free(cmd);
			context->start = context->i + 1;
		}
		(context->i)++;
	}
}

// Fonction pour diviser la chaîne en commandes
void	splitage_quote(t_cmd_index *cmdI, const char *str)
{
	t_split	context;
	char	*cmd;

	context.start = 0;
	context.in_quotes = 0;
	context.i = 0;
	process_split(cmdI, str, &context);
	if (context.start < context.i)
	{
		cmd = extract_and_trim_cmd(str, context.start, strlen(str) - 1);
		pushback_cmd(cmd, cmdI, 0);
		free(cmd);
	}
}

int	split_quotes(char *str, t_cmd_index *cmd_index)
{
	int	nb_cmd;

	nb_cmd = 0;
	if (count_double_quote(str) == 1 || count_simple_quote(str) == 1)
		return (-1);
	nb_cmd = how_many_cmd(str);
	if (nb_cmd == -1)
	{
		ft_putstr_fd("Error: pipe\n", 2);
		return (nb_cmd);
	}
	else if (nb_cmd == 1)
	{
		pushback_cmd(str, cmd_index, 1);
		return (nb_cmd);
	}
	else
	{
		splitage_quote(cmd_index, str);
		return (nb_cmd);
	}
}
