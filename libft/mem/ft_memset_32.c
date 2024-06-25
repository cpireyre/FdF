#include <stddef.h>
#include <stdint.h>

void	*ft_memset_32(void *b, uint32_t c, size_t len)
{
	uint32_t	*pb;

	pb = (uint32_t *)b;
	while (len--)
		*pb++ = c;
	return (b);
}

