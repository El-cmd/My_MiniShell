#include "../minishell.h"

void    begin_end_file(int i, t_redir *red, char *str)
{
    red->begin = i;
    while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != ' ')
        i++;
    red->end = i - 1;
}