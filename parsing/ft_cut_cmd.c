#include "../minishell.h"

char	**ft_init_char(char *line)
{
	char	**line_second;
	int i;

	i = 0;
	line_second = ft_split(line, '|');
	while (line_second[i])
	{
		line_second[i] = ft_strtrim(line_second[i], " ");
		i++;
	}
	return (line_second);
}
