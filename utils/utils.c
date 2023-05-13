/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:23:42 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:23:43 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void	pass_space(char *str, int *i);
int		is_end_redir(char c);
void 	no_str(char *cmd);
void	get_file(char *str, int *i);
void	printTitle(void);
*/
//passe les espace et les tabulation
void	pass_space(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t' )
		(*i)++;
}

//regarde si cest la fin d'une string pour les redirection
int		is_end_redir(char c)
{
	if (c == '\0' || c == '<' || c == '>')
	{
		ft_putstr_fd(ERROR_TOKEN, 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//regarde si la commande est vide
void no_str(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		exit(0);
}

void	get_file(char *str, int *i)
{
	while (str[*i] && str[*i] != '>' && str[*i] != '<' && str[*i] != ' ')
		(*i)++;
}

void   printTitle(void)
{
	printf(".-.   .-..-..-. .-..-. .----..-. .-..----..-.   .-.\n");
	printf("|  `.'  || ||  `| || |{ {__  | {_} || {_  | |   | |\n");
	printf("| |\\ /| || || |\\  || |.-._} }| { } || {__ | `--.| |--.\n");
	printf("`-' ` `-'`-'`-' `-'`-'`----' `-' `-'`----'`----'`----'\n");
}

