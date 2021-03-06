/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 12:54:39 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 13:28:51 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

int			ft_check(t_map *map, int x, int y)
{
	int n;
	int co;

	co = 0;
	n = -1;
	while (++n < map->nb_point)
	{
		if (map->map[map->piece[n].y + y][map->piece[n].x + x] != 0 &&
			map->map[map->piece[n].y + y][map->piece[n].x + x] != 1)
			return (0);
		if (map->map[map->piece[n].y + y][map->piece[n].x + x] == 1)
			co++;
	}
	if (co != 1)
		return (0);
	return (1);
}

int			ft_check_enemie_co(t_map *map, int x, int y)
{
	int		co;
	int		n;
	t_point	point;

	co = 0;
	n = -1;
	while (++n < map->nb_point)
	{
		point.x = map->piece[n].x + x;
		point.y = map->piece[n].y + y;
		if ((point.x > 0 && map->map[point.y][point.x - 1] == -1) ||
			(point.x < map->size.x - 1 && map->map[point.y][point.x + 1] == -1)
			|| (point.y > 0 && map->map[point.y - 1][point.x] == -1) ||
			(point.y < map->size.y - 1 && map->map[point.y + 1][point.x] == -1))
			co++;
	}
	return (co);
}

static void	ft_close_enemie_point(t_map *map, int xp, int yp)
{
	int x;
	int y;
	int dis;

	dis = -1;
	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
		{
			if (map->map[y][x] == -1 && ((ft_abs(xp - x)
				+ ft_abs(yp - y) < dis) || dis == -1))
			{
				dis = ft_abs(xp - x) + ft_abs(yp - y);
				map->enemie.x = x;
				map->enemie.y = y;
			}
		}
	}
}

int			ft_close_point(t_map *map, int x, int y)
{
	int		n;
	t_point	point;
	int		dis;

	n = -1;
	ft_close_enemie_point(map, x + map->piece_len.x / 2,
		y + map->piece_len.y / 2);
	dis = ft_abs(x + map->piece[0].x - map->enemie.x)
		+ ft_abs(y + map->piece[0].y - map->enemie.y);
	while (++n < map->nb_point)
	{
		point.x = x + map->piece[n].x;
		point.y = y + map->piece[n].y;
		if (ft_abs(point.x - map->enemie.x)
			+ ft_abs(point.y - map->enemie.y) < dis)
		{
			dis = ft_abs(point.x - map->enemie.x)
				+ ft_abs(point.y - map->enemie.y);
		}
	}
	return (dis);
}
