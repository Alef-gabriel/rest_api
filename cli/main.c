#include "../include/cli.h"

static void	exit_with_error(void)
{
	printf("Error: Use -h or help flags\n");
	exit (1);
}

int	parser_argv(char **argv)
{
	if (argv[1] == NULL)
		return (2);
	else if (argv[1] && (strncmp(argv[1], "help", strlen(argv[1])) == 0
		|| strncmp(argv[1], "-h", strlen(argv[1])) == 0))
	{
		printf("\\* CLI Help : Later \"./cli\" use -s for to view static and -r for viw in real time /*\n");
		exit (0);
	}
	else if (argv[1] && strncmp(argv[1], "-r", strlen(argv[1])) == 0)
		return (1);
	else if (argv[1] && strncmp(argv[1], "-s", strlen(argv[1])) == 0)
		return (2);
	else
		exit_with_error();
	return(2);
}

int	main(int argc, char *argv[])
{
	char	*put;
	int		fd;
	int		type;


	if (argc <= 2)
		type = parser_argv(argv);
	else
		exit_with_error();
	fd = open("logs.log", O_RDONLY, 0644);
	put = "--------------------------------------------------\n|   METHOD   |   URI   |   TIME\n";
	printf("%s", put);
	printf("--------------------------------------------------\n");
	while (type)
	{
		while (put = get_next_line(fd))
		{
			put = ft_strjoin("|   ", put);
			printf("%s", put);
			free(put);
		}
		if (type == 2)
			break;
	}
	close(fd);
	return (0);
}