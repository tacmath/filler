/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   util.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 16:58:16 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

static void	ft_get_start(t_map *map, int x, int y)
{
	x = (map->size.x - map->size.x / 4) / map->plateau.x;
	y = ((map->size.y - 260) - (map->size.y - 260) / 10) / map->plateau.y;
	if (x < y)
	{
		map->start.x = ft_abs(x * map->plateau.x - map->size.x) / 2;
		map->start.y = ft_abs(x * map->plateau.y -
			(map->size.y - 260)) / 2 + 260;
		map->pix_len = x;
	}
	else
	{
		map->start.x = ft_abs(y * map->plateau.x - map->size.x) / 2;
		map->start.y = ft_abs(y * map->plateau.y -
			(map->size.y - 260)) / 2 + 260;
		map->pix_len = y;
	}
	y = map->start.y - 1;
	while (++y < map->pix_len * map->plateau.y + map->start.y)
	{
		x = map->start.x - 1;
		while (++x < map->size.x - map->start.x)
			map->data[x + y * map->size.x] = 0x252525;
	}
}

void		ft_get_len_plateau(t_map *map, char *line)
{
	int n;

	if (map->plateau.x == 0 || map->plateau.y == 0)
	{
		map->plateau.y = ft_atoi(&(line[7]));
		n = 8;
		while (line[++n] != ' ')
			;
		map->plateau.x = ft_atoi(&(line[n]));
		ft_get_start(map, 0, 0);
	}
}

void		ft_free_map(t_map *map)
{
	free(map->player1);
	free(map->player2);
	free(map->path);
	mlx_destroy_image(map->mlx_ptr, map->img_ptr);
	mlx_destroy_image(map->mlx_ptr, map->filler);
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	free(map->mlx_ptr);
	free(map);
}
