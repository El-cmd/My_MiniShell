#include "minishell.h"

void	newline(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	newline();
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	const char *line;
	char **line_second;
	line = malloc(sizeof(char *) * BUFFER_SIZE_MAX);
	t_token_line *prout;
	t_envSom *doberman = init_envp(envp);
	prout = NULL;

	signal(SIGINT, &sigint_handler);
	if (!line)
	{
		perror("Malloc failure\n");
		return (EXIT_FAILURE);
	}
	while(1)
	{
		line = readline( "MS >> 🤖: " );
		prout = ft_tk_line((char *)line);
		line_second = ft_init_char((char *)line);
		make_list(line_second, prout, envp, doberman);
		add_history(line);
		free((void*)line);
		free(prout);
	}
	return (0);
}