#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "transform.h"
#include <sys/stat.h>
#include <stdio.h>

void	serialize(t_transform T)
{
	int	fd;
	mode_t	old_umask;

	old_umask = umask(022);
	fd = open("./.state", O_RDWR | O_TRUNC | O_CREAT, 0644);
	umask(old_umask);
	if (fd < 0)
	{
		ft_dprintf(2, "Open errored\nmore specifically:");
		perror(NULL);
		return ;
	}
	ft_dprintf(fd, "%d\n", T.rotation.x);
	ft_dprintf(fd, "%d\n", T.rotation.y);
	ft_dprintf(fd, "%d\n", T.rotation.z);
	ft_dprintf(fd, "%d\n", T.scale);
	ft_dprintf(fd, "%d\n", T.offset_x);
	ft_dprintf(fd, "%d\n", T.offset_y);
	ft_dprintf(2, "Successfully serialized\n");
	close(fd);
}

t_transform	deserialize(int default_width, int default_height)
{
	int	fd;
	t_transform	T;
	char	buf[256];
	ssize_t		ret;
	char		*ptr;

	T.scale = 100;
	T.offset_x = default_width / 3;
	T.offset_y = default_height / 2;
	T.rotation.x = 0;
	T.rotation.y = 0;
	T.rotation.z = 0;
	fd = open("./.state", O_RDONLY);
	if (fd < 0)
		return (T);
	ret = read(fd, buf, 256);
	close(fd);
	if (ret <= 0)
		return (T);
	buf[ret] = '\0';
	ptr = buf;
	ft_dprintf(2, "read from file:\n%s\n", ptr);
	T.rotation.x = ft_atoi(ptr);
	ptr = ft_strchr(ptr, '\n');
	T.rotation.y = ft_atoi(++ptr);
	ptr = ft_strchr(ptr, '\n');
	T.rotation.z = ft_atoi(++ptr);
	ptr = ft_strchr(ptr, '\n');
	T.scale = ft_atoi(++ptr);
	ptr = ft_strchr(ptr, '\n');
	T.offset_x = ft_atoi(++ptr);
	ptr = ft_strchr(ptr, '\n');
	T.offset_y = ft_atoi(++ptr);
	ft_dprintf(2, "%d\n", T.rotation.x);
	ft_dprintf(2, "%d\n", T.rotation.y);
	ft_dprintf(2, "%d\n", T.rotation.z);
	ft_dprintf(2, "%d\n", T.scale);
	ft_dprintf(2, "%d\n", T.offset_x);
	ft_dprintf(2, "%d\n", T.offset_y);
	ft_dprintf(2, "Successfully deserialized\n");
	return (T);
}
