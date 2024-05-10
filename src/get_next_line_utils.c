#include <stdlib.h>

char	*ft_strcat(char *dst, const char *src);
char	*ft_strndup(const char *src, size_t n);

char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	char	*dup;

	i = 0;
	while (src[i] && i < n)
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dup[j] = src[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}
