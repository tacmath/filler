/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 12:54:39 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 14:31:23 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

int	ft_check(t_map *map, int x, int y)
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
