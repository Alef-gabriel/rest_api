#include "../include/cli.h"

void	ft_delete(char **buf)
{
	int		i;

	i = 0;
	if (*buf)
	{
		while ((*buf)[i])
			(*buf)[i++] = 0;
		free(*buf);
		*buf = NULL;
	}
}

int	ft_buf_verify(char *buf)
{
	if (*buf)
		return (BUFFER_SIZE);
	return (0);
}
