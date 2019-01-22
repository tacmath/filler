/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 14:49:02 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 16:59:59 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

int ft_get_map(t_map *map, char *line)
{
	int n;

	n = -1;
	while (ft_strncmp(line, "Plateau", 7))
	{
		free(line);
		get_next_line(0, &line);
	}
	map->size.y = ft_atoi(&(line[8]));
	map->size.x = ft_atoi(&(line[11]));
	free(line);
	get_next_line(0, &line);
	free(line);
	if (!(map->map = malloc(sizeof(char*) * map->size.y)))
		return (0);
	while (++n < map->size.y)
	{
		get_next_line(0, &line);
		map->map[n] = ft_strdup(&(line[4]));
		free(line);
	}
	return (1);
}

int ft_piece_realloc(t_map *map, int x, int y)
{
	t_point *tmp_piece;
	int		n;

	map->nb_point++;
	if (!(tmp_piece = malloc(sizeof(t_point) * map->nb_point)))
		return (0);
	n = -1;
	while (++n < map->nb_point - 1)
		tmp_piece[n] = map->piece[n];
	tmp_piece[n].x = x;
	tmp_piece[n].y = y;
	ft_memdel((void*)(&map->piece));
	map->piece = tmp_piece;
	return (1);
}

int ft_get_piece(t_map *map)
{
	int n;
	t_point coord;
	char *line;

	map->nb_point = 0;
	get_next_line(0, &line);
	coord.y = ft_atoi(&(line[5]));
	free(line);
	n = -1;
	while (++n < coord.y)
	{
		get_next_line(0, &line);
		coord.x = -1;
		while (line[++coord.x])
		{
			if (line[coord.x] == '*')
				ft_piece_realloc(map, coord.x, n);
		}
		free(line);
	}
	return (1);
}

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

int ft_check_co(t_map *map, int x, int y)
{
	if (y - 1 > 0 && map->map[y - 1][x] == map->player)
		return (1);
	if (y + 1 < map->size.y && map->map[y + 1][x] == map->player)
		return (1);
	if (x - 1 > 0 && map->map[y][x - 1] == map->player)
		return (1);
	if (x + 1 < map->size.x && map->map[y][x + 1] == map->player)
		return (1);
	return (0);
}

int ft_check(t_map *map, int x, int y)
{
	int n;
	int co;

	co = 0;
	n = -1;
	while (++n < map->nb_point)
	{
		if (map->map[map->piece[n].y + y][map->piece[n].x + x] != '.')
			return (0);
		if (ft_check_co(map, map->piece[n].x + x, map->piece[n].y + y))
			co++;
	}
	if (co == 0)
		return (0);
	return (1);
}

int main(void)
{
	t_map	*map;
	char	*line;

	if (!(map = malloc(sizeof(t_map))))
		return (0);
	map->piece = 0;
	get_next_line(0, &line);
	if (line[10] == '1')
		map->player = 'O';
	else if (line[10] == '2')
		map->player = 'X';
	ft_get_map(map, line);
	ft_get_piece(map);
	ft_normalise(map);
	return (0);
}
