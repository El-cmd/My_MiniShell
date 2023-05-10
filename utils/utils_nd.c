#include "../minishell.h"

// decoupe les fichier de redirection
void    begin_end_file(int i, t_redir *red, char *str)
{
    red->begin = i;
    while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != ' ')
        i++;
    red->len = i - red->begin;
    red->file = ft_substr(str, red->begin, red->len);
}