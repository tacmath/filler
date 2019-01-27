/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 12:49:40 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/27 14:54:36 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

char	*ft_get_line(t_map *map, char *dest)
{
	int n;
	int m;
	char *str;

	if (get_next_line(0, &str) < 1)
		return (0);
	n = -1;
	m = 0;
	while (str[++n] != ' ')
		;
	while (str[++n])
	{
		if (str[n] == '.')
			dest[m] = 0;
		else if (str[n] == map->player)
			dest[m] = 1;
		else
			dest[m] = -1;
		m++;
	}
	free(str);
	return (dest);
}

int ft_get_map(t_map *map, char *line)
{
	int n;

	n = -1;
	map->size.y = ft_atoi(&(line[8]));
	map->size.x = ft_atoi(&(line[11]));
	free(line);
	get_next_line(0, &line);
	free(line);
	if (!(map->map = malloc(sizeof(char*) * map->size.y)))
		return (0);
	while (++n < map->size.y)
	{
		if (!(map->map[n] = malloc(sizeof(char) * map->size.x)))
			return (0);
		map->map[n] = ft_get_line(map, map->map[n]);
	}
	return (1);
}

static int ft_piece_realloc(t_map *map, int x, int y)
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
	ft_normalise(map);
	ft_get_piece_len(map);
	ft_resolve(map);
	return (1);
}

int ft_fill_map(t_map *map)
{
	char *line;
	int n;

	n = -1;
	get_next_line(0, &line);
	free(line);
	while (++n < map->size.y)
		map->map[n] = ft_get_line(map, map->map[n]);
	ft_get_piece(map);
	return (1);
}

