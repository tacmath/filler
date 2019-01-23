/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 12:52:06 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 13:29:14 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

void ft_normalise(t_map *map)
{
	int n;
	t_point min;

	min.x = map->piece[0].x;
	min.y = map->piece[0].y;
	n = 0;
	while (++n < map->nb_point)
	{
		if (map->piece[n].x < min.x)
			min.x = map->piece[n].x;
		if (map->piece[n].y < min.y)
			min.y = map->piece[n].y;
	}
	n = -1;
	while (++n < map->nb_point)
	{
		map->piece[n].x -= min.x;
		map->piece[n].y -= min.y;
	}
	map->piece_start = min;
}

void ft_get_piece_len(t_map *map)
{
	int n;

	n = 0;
	map->piece_len.x = map->piece[0].x;
	map->piece_len.y = map->piece[0].y;
	while (++n < map->nb_point)
	{
		if (map->piece[n].x > map->piece_len.x)
			map->piece_len.x = map->piece[n].x;
		if (map->piece[n].y > map->piece_len.y)
			map->piece_len.y = map->piece[n].y;
	}
}

void ft_free_struct(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->size.y)
		free(map->map[n]);
	free(map->map);
	free(map->piece);
	free(map);
}
