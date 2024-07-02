/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:28:17 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 11:30:47 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "transform.h"

static t_transform	parse_transform(const char *deserialized);

void	serialize(t_transform transform)
{
	int	fd;

	fd = open("./.state", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return ;
	ft_dprintf(fd, "%d\n", transform.rotation.x);
	ft_dprintf(fd, "%d\n", transform.rotation.y);
	ft_dprintf(fd, "%d\n", transform.rotation.z);
	ft_dprintf(fd, "%d\n", transform.scale);
	ft_dprintf(fd, "%d\n", transform.offset_x);
	ft_dprintf(fd, "%d\n", transform.offset_y);
	close(fd);
}

t_transform	deserialize(int default_width, int default_height)
{
	char		buf[256];
	int			fd;
	ssize_t		ret;
	t_transform	transform;

	transform.scale = 100;
	transform.offset_x = default_width / 3;
	transform.offset_y = default_height / 2;
	transform.rotation.x = 0;
	transform.rotation.y = 0;
	transform.rotation.z = 0;
	fd = open("./.state", O_RDONLY);
	if (fd < 0)
		return (transform);
	ret = read(fd, buf, 256);
	close(fd);
	if (ret <= 0)
		return (transform);
	buf[ret] = '\0';
	return (parse_transform(buf));
}

static t_transform	parse_transform(const char *deserialized)
{
	t_transform	transform;

	transform.rotation.x = ft_atoi(deserialized);
	deserialized = ft_strchr(deserialized, '\n');
	transform.rotation.y = ft_atoi(++deserialized);
	deserialized = ft_strchr(deserialized, '\n');
	transform.rotation.z = ft_atoi(++deserialized);
	deserialized = ft_strchr(deserialized, '\n');
	transform.scale = ft_atoi(++deserialized);
	deserialized = ft_strchr(deserialized, '\n');
	transform.offset_x = ft_atoi(++deserialized);
	deserialized = ft_strchr(deserialized, '\n');
	transform.offset_y = ft_atoi(++deserialized);
	return (transform);
}
