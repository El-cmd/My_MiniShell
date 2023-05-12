#include "../minishell.h"

int is_redir_or_cmd(char c)
{
    if (c == '<' || c == '>')
        return 1;
    return 0;
}

void cut(t_cmd *cmd, int *i)
{
    int start;
    int end;

    start = *i;
    while (is_redir_or_cmd(cmd->cmd[*i]) == 0 && cmd->cmd[*i] != '\0')
        (*i)++;
    end = *i;
    cmd->just_cmd = ft_substr(cmd->cmd, start, (end - start));    
}