/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 12:49:40 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 13:37:34 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

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

int ft_fill_map(t_map *map)
{
	char *line;
	int n;

	n = -1;
	while (ft_strncmp(line, "Plateau", 7))
	{
		get_next_line(0, &line);
		free(line);
	}
	get_next_line(0, &line);
	free(line);
	while (ft_strncmp(line, "Plateau", 7))
	{
		get_next_line(0, &line);
		free(line);
	}
	get_next_line(0, &line);
	free(line);
	while (++n < map->size.y)
	{
		get_next_line(0, &line);
		map->map[n] = ft_strcpy(map->map[n], &(line[4]));
		free(line);
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
	return (1);
}