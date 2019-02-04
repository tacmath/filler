/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 12:25:48 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 13:36:40 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

static int	ft_usage(void)
{
	write(1, "usage : ./map_gen <map name> <lenth> <height>\n", 47);
	write(1, "lenth  [4 - 300]\n", 17);
	write(1, "hieght [4 - 300]\n", 17);
	return (0);
}

static void	ft_put_map(int length, int height, int fd)
{
	int		x;
	int		y;
	int		nrand;

	srand((unsigned int)time(NULL));
	nrand = 1 + rand() % (length * (height - 1) / 2);
	y = -1;
	while (++y < height)
	{
		if (y == height / 2)
			nrand = 1 + rand() % (length * (height - 1) / 2);
		x = -1;
		while (++x < length)
		{
			if (--nrand == 0 && y < height / 2)
				ft_putchar_fd('O', fd);
			else if (nrand == 0 && y >= height / 2)
				ft_putchar_fd('X', fd);
			else
				ft_putchar_fd('.', fd);
		}
		ft_putchar_fd('\n', fd);
	}
}

int			main(int ac, char **av)
{
	int		length;
	int		height;
	char	*tmp;
	int		fd;

	if (ac != 4 || ft_atoi(av[2]) > 300 || ft_atoi(av[2]) < 4 ||
		ft_atoi(av[3]) > 300 || ft_atoi(av[3]) < 4)
		return (ft_usage());
	length = ft_atoi(av[2]);
	height = ft_atoi(av[3]);
	if (!(tmp = ft_strjoin("maps/", av[1])))
		return (0);
	if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		return (0);
	free(tmp);
	ft_put_map(length, height, fd);
	if ((close(fd) == -1))
		return (0);
	return (1);
}
