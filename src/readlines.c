#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

char	**read_lines(const char *path);
static char	*slurp(const char *path);
static char	*read_file(int fd);
static char	*append(char *s1, char *s2);

char	**read_lines(const char *path)
{
	char	**lines;
	char	*file;

	file = slurp(path);
	if (!file)
		return (NULL);
	lines = ft_split(file, '\n');
	if (!lines)
		return (NULL);
	return (lines);
}

static char	*slurp(const char *path)
{
	int	fd;
	char	*ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	ret = read_file(fd);
	if (!ret)
		return (NULL);
	close(fd);
	return (ret);
}

#define BUFSIZ 512

static char	*read_file(int fd)
{
	char	*acc;
	char	chunk[BUFSIZ + 1];
	ssize_t	bytes_read;

	bytes_read = 1;
	acc = NULL;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, chunk, BUFSIZ);
		chunk[bytes_read] = '\0';
		acc = append(acc, chunk);
		if (!acc)
			return (NULL);
	}
	if (bytes_read < 0)
		free(acc);
	return (acc);
}

static char	*append(char *s1, char *s2)
{
	char	*merged;
	size_t	merged_length;

	merged_length = ft_strlen(s2);
	if (s1)
		merged_length += ft_strlen(s1);
	merged = malloc(merged_length + 1);
	if (!merged)
		return (NULL);
	merged[0] = '\0';
	if (s1)
		ft_strlcat(merged, s1, merged_length + 1);
	ft_strlcat(merged, s2, merged_length + 1);
	free(s1);
	return (merged);
}
