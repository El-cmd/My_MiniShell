#include "minishell.h"


// Les Signaux
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
void sigquit_handler(int sig)
{
	(void)sig;
	ft_putendl_fd("CTRL-D = Segmentation fault", 2);
	exit(0);
}
//

void printtest(t_cmdIndex *cmd)
{
	printf("cmd->nb_cmd = %d\n", cmd->nb_cmd);
	printf("cmd->nb_pipe = %d\n", cmd->nb_pipe);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	const char *line;
	char **Nenv; 
	//char **line_second;
	line = malloc(sizeof(char *) * BUFFER_SIZE_MAX);
	t_envSom *doberman = init_envp(envp);
	t_cmdIndex *cmdIndex;
	(void)doberman;
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, &sigquit_handler);
	if (!line)
	{
		perror("Malloc failure\n");
		return (EXIT_FAILURE);
	}
	printTitle();
	while(1)
	{
		line = readline( "MS >> 🤖: " );
		cmdIndex = init_cmd();
		Nenv = ft_getpath(doberman);
		splitOrNot((char *)line, cmdIndex);
		exec(cmdIndex, Nenv, doberman);
		add_history(line);
		free((void*)line);
	}
	return (0);
}
