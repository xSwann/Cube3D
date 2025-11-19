#include "../../headers/cube3D.h"

void	ft_putstr_fd(char *s, int fd)
{
	ssize_t	ret;

	if (s)
		ret = write(fd, s, ft_strlen(s));
	(void)ret;
}

int	is_valid_path(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
