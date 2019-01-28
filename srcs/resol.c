/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resol.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/27 12:09:50 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 14:17:25 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

int ft_check_enemie_co(t_map *map, int x, int y)
{
	int co;
	int n;
	t_point point;

	co = 0;
	n = -1;
	while (++n < map->nb_point)
	{
		point.x = map->piece[n].x + x;
		point.y = map->piece[n].y + y;
		if (point.x > 0 && map->map[point.y][point.x - 1] == -1)
			co++;
		else if (point.x < map->size.x - 1 && map->map[point.y][point.x + 1] == -1)
			co++;
		else if (point.y > 0 && map->map[point.y - 1][point.x] == -1)
			co++;
		else if (point.y < map->size.y - 1 && map->map[point.y + 1][point.x] == -1)
			co++;		
	}
	return (co);
}

int ft_close_point(t_map *map, int x, int y)
{
	int n;
	t_point point;
	int dis;

	n = -1;
	dis = ft_abs(x + map->piece[0].x - map->enemie.x) + ft_abs(y + map->piece[0].y - map->enemie.y);
	while (++n < map->nb_point)
	{
		point.x = x + map->piece[n].x;
		point.y = y + map->piece[n].y;
		if (ft_abs(point.x - map->enemie.x) + ft_abs(point.y - map->enemie.y) < dis)
			dis = ft_abs(point.x - map->enemie.x) + ft_abs(point.y - map->enemie.y);
	}
	return (dis);
}

void ft_resolve(t_map *map)
{
	int x;
	int y;
	int dis;
	t_point place;
	int co_enemie;

	dis = -1;
	co_enemie = 0;
	place.x = -1;
	place.y = -1;
	y = -1;
	while (++y < map->size.y - map->piece_len.y)
	{
		x = -1;
		while (++x < map->size.x - map->piece_len.x)
			if (ft_check(map, x, y))
			{
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
	ft_putnbr(place.y - map->piece_start.y);
	ft_putchar(' ');
	ft_putnbr(place.x - map->piece_start.x);
	ft_putchar('\n');
}
