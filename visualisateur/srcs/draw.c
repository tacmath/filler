/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 15:57:56 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 17:01:06 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

void		ft_put_point(t_map *map, int x, int y, int color)
{
	t_point coord;

	if (color == map->p1_color)
		map->p1_point++;
	else if (color == map->p2_color)
		map->p2_point++;
	coord.y = y * map->pix_len + map->start.y;
	while (++coord.y < (y + 1) * map->pix_len + map->start.y - 1)
	{
		coord.x = x * map->pix_len + map->start.x;
		while (++coord.x < (x + 1) * map->pix_len + map->start.x - 1)
			map->data[coord.x + coord.y * map->size.x] = color;
	}
}

static void	ft_put_player(t_map *map)
{
	int		x;
	char	*tmp;

	x = map->size.x / 2 - 150 - (ft_strlen(map->player1) * 10) / 2;
	mlx_string_put(map->mlx_ptr, map->win_ptr,
		x, 220, map->p1_color, map->player1);
	x = map->size.x / 2 + 150 - (ft_strlen(map->player2) * 10) / 2;
	mlx_string_put(map->mlx_ptr, map->win_ptr,
		x, 220, map->p2_color, map->player2);
	tmp = ft_itoa(map->p1_point);
	x = 80 - (ft_strlen(tmp) * 10) / 2;
	mlx_string_put(map->mlx_ptr, map->win_ptr,
		x, map->start.y - 25, map->p1_color, tmp);
	free(tmp);
	tmp = ft_itoa(map->p2_point);
	x = map->size.x - 80 - (ft_strlen(tmp) * 10) / 2;
	mlx_string_put(map->mlx_ptr, map->win_ptr,
		x, map->start.y - 25, map->p2_color, tmp);
	free(tmp);
}

static void	ft_p1_score(t_map *map)
{
	int		x;
	int		y;
	int		color;
	double	point_per_line;

	point_per_line = map->pix_len / (double)map->plateau.x;
	color = map->p1_color;
	y = map->start.y - 1;
	while (++y < map->pix_len * map->plateau.y + map->start.y)
	{
		x = 50 - 1;
		while (++x < 110)
		{
			if (map->pix_len * map->plateau.y - (y - map->start.y)
				< point_per_line * map->p1_point)
				map->data[x + y * map->size.x] = color;
			else
				map->data[x + y * map->size.x] = ft_rgb(ft_hextor(color) / 2,
					ft_hextog(color) / 2, ft_hextob(color) / 2);
		}
	}
}

static void	ft_p2_score(t_map *map)
{
	int		x;
	int		y;
	int		color;
	double	point_per_line;

	point_per_line = map->pix_len / (double)map->plateau.x;
	color = map->p2_color;
	y = map->start.y - 1;
	while (++y < map->pix_len * map->plateau.y + map->start.y)
	{
		x = map->size.x - 110 - 1;
		while (++x < map->size.x - 50)
		{
			if (map->pix_len * map->plateau.y - (y - map->start.y)
				< point_per_line * map->p2_point)
				map->data[x + y * map->size.x] = color;
			else
				map->data[x + y * map->size.x] = ft_rgb(ft_hextor(color) / 2,
					ft_hextog(color) / 2, ft_hextob(color) / 2);
		}
	}
}

void		ft_draw(t_map *map)
{
	ft_p1_score(map);
	ft_p2_score(map);
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
		map->filler, (map->size.x - 850) / 2, 10);
	ft_put_player(map);
}
