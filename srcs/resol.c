/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resol.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/27 12:09:50 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/27 14:48:23 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

int ft_check_enemie_co(t_map *map, int x, int y)
{
	int co;
	int n;

	co = 0;
	n = -1;
	while (++n < map->nb_point)
	{
		if (x > 0 && map->map[map->piece[n].y + y][map->piece[n].x + x - 1] == -1)
			co++;
		else if (x < map->size.x && map->map[map->piece[n].y + y][map->piece[n].x + x + 1] == -1)
			co++;
		else if (y > 0 && map->map[map->piece[n].y + y - 1][map->piece[n].x + x] == -1)
			co++;
		else if (y < map->size.x && map->map[map->piece[n].y + y + 1][map->piece[n].x + x] == -1)
			co++;		
	}
	return (co);
}

int ft_close_point(t_map *map, int x, int y)
{
	int n;
	int dis;

	dis = 0;
	n = -1;
	x += map->piece_start.x;
	y += map->piece_start.y;
	while (++n < map->nb_point)
		if (ft_abs(x + map->piece[n].x - map->enemie.x) + ft_abs(y + map->piece[n].y - map->enemie.y) < dis)
			dis = ft_abs(x + map->piece[n].x - map->enemie.x) + ft_abs(y + map->piece[n].y - map->enemie.y);
	return (dis);
}

void	ft_put_piece_to_map(t_map *map, int x, int y)
{
	int n;

	n = -1;
	while (++n < map->nb_point)
		map->map[y + map->piece[n].y][x + map->piece[n].x] = 1;
}

void ft_resolve(t_map *map)
{
//	int fd;
	int x;
	int y;
	int dis;
	t_point place;
	int co_enemie;

	dis = -1;
	co_enemie = -1;
	place.x = 0;
	place.y = 0;
	y = -1;
//	fd = open("test.txt", O_WRONLY | O_CREAT, 777);
	while (++y < map->size.y - map->piece_len.y)
	{
		x = -1;
		while (++x < map->size.x - map->piece_len.x)
			if (ft_check(map, x, y))
			{
				//ft_putchar_fd('a', fd);
				//ft_putchar_fd('\n', fd);
				if (co_enemie < ft_check_enemie_co(map, x, y))
				{
					co_enemie = ft_check_enemie_co(map, x, y);
					place.x = x;
					place.y = y;
				}
				else if (co_enemie == 0 && (ft_close_point(map, x, y) < dis || dis == -1))
				{
					dis = ft_close_point(map, x, y);
					place.x = x;
					place.y = y;
				}
			}
	}
/*	
	ft_putnbr_fd(place.x - map->piece_start.x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(place.y - map->piece_start.y, fd);
	ft_putchar_fd('\n', fd);
	close(fd);*/
	ft_put_piece_to_map(map, place.x, place.y);
	ft_putnbr(place.y - map->piece_start.y);
	ft_putchar(' ');
	ft_putnbr(place.x - map->piece_start.x);
	ft_putchar('\n');
}
