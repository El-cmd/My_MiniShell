/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:37 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:24:38 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//malloc les redirections pour toute les cmd
void	malloc_all(t_data *data)
{
	redirOrNot(data->cmdIndex);
	initRedirOrnot(data->cmdIndex);
	malloc_redir(data);
    exec_find_cmd(data);
}

//Open des file parser plus haut, dans lexec si fd = -1 exit le process
void    ft_open(t_redir *red)
{
    if (red->type == APPEND)
        red->fd = open(red->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else if (red->type == R_OUT)
        red->fd = open(red->file,  O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (red->type == R_IN)
        red->fd = open(red->file, O_RDONLY, 0644);
}

//decoupe les fichier de redirection et open les file en en mettant les fd dans ls struct
void    begin_end_file(int i, t_redir *red, char *str)
{
    red->begin = i;
    while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != ' ')
        i++;
    red->len = i - red->begin;
    red->file = ft_substr(str, red->begin, red->len);
    ft_open(red);    
}