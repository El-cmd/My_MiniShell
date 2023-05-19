/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:29:24 by vloth             #+#    #+#             */
/*   Updated: 2023/05/19 17:58:49 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void is_meta(t_data *data)
{
    int i;
    t_cmd *cmd;

    i = 0;
    cmd = data->cmdIndex->begin;
    while (cmd)
    {
        while (cmd->cmd[i])
        {
            if (cmd->cmd[i] == '$')
                cmd->have_meta = true;
            i++;
        }
        i = 0;
        cmd = cmd->next;    
    }
}

//void pars_meta(t_data *cmd)
//{
//    
//}