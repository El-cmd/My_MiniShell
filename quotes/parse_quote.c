#include "../minishell.h"

int	how_many_cmd(char *str)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = parseur_quotes(str, i + 1, str[i]) + 1;
		if (str[i] == '|')
			j++;
		i++;
	}
	return (j);
}

void split_quotes(char *str, t_cmdIndex *cmdIndex)
{
	(void)cmdIndex;
	int nb_cmd;

	nb_cmd = 0;
	if (count_double_quote(str) == 1 || count_simple_quote(str) == 1)
		return ;
	nb_cmd = how_many_cmd(str);
	if (nb_cmd == -1)
	{
		ft_putstr_fd("Error: pipe\n", 2);
		return ;
	}
	else if (nb_cmd == 1)
	{
		pushback_cmd(str, cmdIndex, 1);
		return ;
	}
}
