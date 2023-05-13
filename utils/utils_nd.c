#include "../minishell.h"

int is_redir_or_cmd(char c)
{
    if (c == '<' || c == '>')
        return 1;
    return 0;
}
