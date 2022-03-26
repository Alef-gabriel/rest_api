#ifndef CLI_H
# define CLI_H
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "api.h"

# define BUFFER_SIZE 42

char	*get_next_line(int fd);
void	ft_delete(char **buf);
int		ft_buf_verify(char *buf);
char	*ft_strjoin(const char *s1, const char *s2);
#endif