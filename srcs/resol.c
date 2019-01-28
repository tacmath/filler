/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resol.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/27 12:09:50 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 15:57:08 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

static void	ft_put_sol(int x, int y)
{
	ft_putnbr(y);
	ft_putchar(' ');
	ft_putnbr(x);
	ft_putchar('\n');
}

static void	ft_point_alloc(t_point *point, int x, int y)
{
	(*point).x = x;
	(*point).y = y;
}

void		ft_resolve(t_map *map, int x, int y, int dis)
{
	t_point	place;
	int		co_enemie;

	co_enemie = 0;
	ft_point_alloc(&place, -1, -1);
	while (++y < map->size.y - map->piece_len.y)
	{
		x = -1;
		while (++x < map->size.x - map->piece_len.x)
			if (ft_check(map, x, y))
			{
				if (co_enemie < ft_check_enemie_co(map, x, y))
				{
					co_enemie = ft_check_enemie_co(map, x, y);
					ft_point_alloc(&place, x, y);
				}
				else if (co_enemie == 0 && (ft_close_point(map, x, y)
						< dis || dis == -1))
				{
					dis = ft_close_point(map, x, y);
					ft_point_alloc(&place, x, y);
				}
			}
	}
	ft_put_sol(place.x - map->piece_start.x, place.y - map->piece_start.y);
}
