#include "../minishell.h"

int find_path(char **env)
{
	int	n;

	n = 0;
	while (env[n] && ft_strncmp(env[n], "PATH=", 5))
		n++;
	return (n);
}


char	**ft_parsing(char **envp)
{
	int		i;
	char	**path;
	char	*tmp;

	i = find_path(envp);
	tmp = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	path = ft_split(tmp, ':');
	free(tmp);
	return (path);
}