#include "../minishell.h"

void cut_arg(t_data *data)
{
    t_cmd *cmd;
    
    cmd = data->cmdIndex->begin;
    while (cmd)
    {
        if (cmd->is_built == false)
        {
            if (cmd->redir)
                cmd->argv = ft_split(cmd->just_cmd, ' ');
            else
                cmd->argv = ft_split(cmd->cmd, ' ');
        }
        cmd = cmd->next;
    }
}
