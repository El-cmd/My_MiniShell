#include "../minishell.h"

void cut_quote(t_data *data)
{
    t_cmd *cmd;
    int i;

    i = 0;
    cmd = data->cmdIndex->begin;
    while (cmd)
    {
        if (cmd->quotes)
        {
            while (cmd->argv[i])
            {
                cmd->argv[i] = ft_strtrim(cmd->argv[i], "\"");
                cmd->argv[i] = ft_strtrim(cmd->argv[i], "\'");
                i++;
            }
            i = 0;
        }
        cmd = cmd->next;
    }
}

void cut_arg(t_data *data)
{
    t_cmd *cmd;
    
    cmd = data->cmdIndex->begin;
    while (cmd)
    {
        if (cmd->redir)
            cmd->argv = ft_split(cmd->just_cmd, ' ');
        else
            cmd->argv = ft_split(cmd->cmd, ' ');
        cmd = cmd->next;
    }
    cut_quote(data);
}

