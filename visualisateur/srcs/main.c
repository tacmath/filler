/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 15:50:03 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

void	ft_get_start(t_map *map)
{
	int x;
	int y;

	x = (map->size.x - map->size.x / 4) / map->plateau.x;
	y = ((map->size.y - 260) - (map->size.y - 260) / 10) / map->plateau.y;
	if (x < y)
	{
		map->start.x = ft_abs(x * map->plateau.x - map->size.x) / 2;
		map->start.y = ft_abs(x * map->plateau.y - (map->size.y - 260)) / 2 + 260;
		map->pix_len = x;
	}
	else
	{
		map->start.x = ft_abs(y * map->plateau.x - map->size.x) / 2;
		map->start.y = ft_abs(y * map->plateau.y - (map->size.y - 260)) / 2 + 260;
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


int ft_put_plateau(t_map *map)
{
	int x;
	int y;
	char *line;

	line = 0;
	map->p1_point = 0;
	map->p2_point = 0;
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
				ft_put_point(map, x, y, map->p1_color);
			else if (line[4 + x] == 'X' || line[4 + x] == 'x')
				ft_put_point(map, x, y, map->p2_color);
		}	
		ft_memdel((void**)&line);
	}
	return (1);
}

int 	ft_winner(t_map *map)
{
	char *tmp;

	if (get_next_line(0, &tmp) < 1)
		return (0);
	free(tmp);
	if (map->p1_point > map->p2_point)
	{
		tmp = ft_strjoin(map->player1, " WIN");
		mlx_string_put(map->mlx_ptr, map->win_ptr, (map->size.x - ft_strlen(tmp) * 10) / 2, 260, map->p1_color, tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_strjoin(map->player2, " WIN");
		mlx_string_put(map->mlx_ptr, map->win_ptr, (map->size.x - ft_strlen(tmp) * 10) / 2, 260, map->p2_color, tmp);
		free(tmp);
	}
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
			ft_draw(map);
		}
		else if (!ft_strncmp("== ", line, 3))
			ft_winner(map);
		ft_memdel((void**)&line);
	}
	return (0);
}

int ft_get_path(t_map *map, char *name)
{
	int n;

	n = ft_strlen(name);
	while (name[--n] != '/')
		;
	map->path = ft_strsub(name, 0, n + 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_map	*map;

	ac = 0;
	if (!(map = malloc(sizeof(t_map))))
		return (0);
	ft_get_path(map, av[0]);
	if (!(ft_struct_init(map)))
		return (0);
	mlx_loop_hook(map->mlx_ptr, ft_loop, map);
	mlx_hook(map->win_ptr, DESTROY_NOTIFY, 0, ft_destroy, map);
	mlx_key_hook(map->win_ptr, deal_key, map);
	mlx_loop(map->mlx_ptr);
	return (1);
}
