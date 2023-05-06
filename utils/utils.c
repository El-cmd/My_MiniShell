#include "../minishell.h"

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

void no_str(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		exit(0);
}