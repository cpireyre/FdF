#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "get_next_line.h"

char		*get_next_line(int fd);
static char	*read_until(int fd, char *buf);
static char	*extract_line(char *buf);
static char	*append(char *s1, char *s2);

/*
 * Returns the next line from the specified file descriptor, handling
 * buffer management internally to preserve data across calls.
 */

char		*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*newline_position;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	newline_position = NULL;
	if (buf)
		newline_position = ft_strchr(buf, '\n');
	if (!newline_position)
		buf = read_until(fd, buf);
	line = NULL;
	if (buf && *buf)
		line = extract_line(buf);
	if (!line)
	{
		free(buf);
		buf = NULL;
	}
	return (line);
}

/*
 * Reads from the file descriptor until a newline character is found
 * or EOF is reached, appending each chunk to the dynamic buffer.
 */

static char	*read_until(int fd, char *buf)
{
	char	chunk[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*newline_position;

	bytes_read = 1;
	newline_position = NULL;
	while (bytes_read > 0 && !newline_position)
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		chunk[bytes_read] = '\0';
		buf = append(buf, chunk);
		if (!buf)
			return (NULL);
		newline_position = ft_strchr(buf, '\n');
	}
	if (bytes_read < 0)
	{
		free(buf);
		buf = NULL;
	}
	return (buf);
}

/*
 * Merges two strings, freeing the first. Ensures the dynamic buffer
 * is appropriately resized and old data discarded.
 * Because append is static and always called from read_until,
 * we know that s2 is never allocated on the heap and never null.
 */

static char	*append(char *s1, char *s2)
{
	char	*merged;
	size_t	merged_length;

	merged_length = ft_strlen(s2);
	if (s1)
		merged_length += ft_strlen(s1);
	merged = malloc(sizeof(char) * (merged_length + 1));
	if (!merged)
		return (NULL);
	merged[0] = '\0';
	if (s1)
		ft_strcat(merged, s1);
	ft_strcat(merged, s2);
	free(s1);
	return (merged);
}

/*
 * Extracts one line from the buffer, adjusting the buffer to
 * remove the extracted line.
 * Manual looping here is as efficient as ft_strlen first, then
 * ft_strchr, but it makes the code simpler because it saves
 * declaring an extra pointer to do pointer arithmetic.
 * We ft_memmove remaining_length + 1 to move the \0 along.
 */

static char	*extract_line(char *buf)
{
	size_t	endline_offset;
	size_t	remaining_length;
	char	*line;

	endline_offset = 0;
	while (buf[endline_offset] && buf[endline_offset] != '\n')
		endline_offset++;
	if (buf[endline_offset] == '\n')
		endline_offset++;
	line = ft_strndup(buf, endline_offset);
	if (!line)
		return (NULL);
	remaining_length = ft_strlen(buf) - endline_offset;
	ft_memmove(buf, buf + endline_offset, remaining_length + 1);
	return (line);
}
