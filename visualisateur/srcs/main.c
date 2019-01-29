/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 16:34:48 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

void	ft_get_start(t_map *map)
{
	int x;
	int y;

	x = (map->size.x - map->size.x / 5) / map->plateau.x;
	y = ((map->size.y - 300) - (map->size.y - 300) / 5) / map->plateau.y;
	if (x < y)
	{
		map->start.x = ft_abs(x * map->plateau.x - map->size.x) / 2;
		map->start.y = ft_abs(x * map->plateau.y - (map->size.y - 300)) / 2 + 300;
		map->pix_len = x;
	}
	else
	{
		map->start.x = ft_abs(y * map->plateau.x - map->size.x) / 2;
		map->start.y = ft_abs(y * map->plateau.y - (map->size.y - 300)) / 2 + 300;
		map->pix_len = y;
	}
	y = map->start.y - 1;
	while (++y < map->pix_len * map->plateau.y + map->start.y + 2)
	{
		x = map->start.x - 1;
		while (++x < map->size.x - map->start.x + 2)
			map->data[x + y * map->size.x] = 0x252525;
	}
}

void	ft_get_len_plateau(t_map *map, char *line)
{
	int n;

	if (map->plateau.x == 0 || map->plateau.y == 0)
	{
		map->plateau.y = ft_atoi(&(line[7]));
		n = 8;
		while (line[++n] != ' ')
			;
		map->plateau.x = ft_atoi(&(line[n]));
		ft_get_start(map);
	}
}

void	ft_put_point(t_map *map, int x, int y, int color)
{
	t_point coord;

	coord.y = y * map->pix_len + map->start.y + 1;
	while (++coord.y < (y + 1) * map->pix_len + map->start.y)
	{
		coord.x = x * map->pix_len + map->start.x + 1;
		while (++coord.x < (x + 1) * map->pix_len + map->start.x)
				map->data[coord.x + coord.y * map->size.x] = color;
	}
}

int ft_put_plateau(t_map *map)
{
	int x;
	int y;
	char *line;

	line = 0;
	y = -1;
	while (++y < map->plateau.y)
	{
		x = -1;
		if (get_next_line(0, &line) < 1)
			return (0);
		while (++x < map->plateau.x)
		{
			if (line[4 + x] == '.')
				ft_put_point(map, x, y, 0x373737);
			else if (line[4 + x] == 'O' || line[4 + x] == 'o')
				ft_put_point(map, x, y, 0xFF0000);
			else if (line[4 + x] == 'X' || line[4 + x] == 'x')
				ft_put_point(map, x, y, 0x00D4FF);
		}	
		ft_memdel((void**)&line);
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->filler, (map->size.x - 850) / 2, 10);
	return (1);
}

int ft_loop(t_map *map)
{
	char *line;

	line = 0;
	if (get_next_line(0, &line) > 0)
	{
		if (!ft_strncmp("Plateau", line, 7))
		{
		if (map->plateau.x == 0 || map->plateau.y == 0)
				ft_get_len_plateau(map, line);
			free(line);
			get_next_line(0, &line);
			ft_memdel((void**)&line);
			ft_put_plateau(map);
		}
		ft_memdel((void**)&line);
	}
	return (0);
}

int	main(void)
{
	t_map	*map;

	if (!(map = malloc(sizeof(t_map))))
		return (0);
	if (!(ft_struct_init(map)))
		return (0);
	mlx_loop_hook(map->mlx_ptr, ft_loop, map);
	mlx_hook(map->win_ptr, DESTROY_NOTIFY, 0, ft_destroy, map);
	mlx_key_hook(map->win_ptr, deal_key, map);
	mlx_loop(map->mlx_ptr);
	return (1);
}
