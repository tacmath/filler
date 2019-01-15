/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 14:49:02 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 16:17:45 by mtaquet     ###    #+. /#+    ###.fr     */
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

int ft_piece_realloc(t_map *map)
{
	t_point *tmp_piece;
	int		n;

	if (!(tmp_piece = malloc(sizeof(t_point) * map->nb_point)))
		return (0);
	n = -1;
	while (++n < map->nb_point - 1)
		tmp_piece[n] = map->piece[n];
	free(map->piece);
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
			{
				map->piece[map->nb_point].x = coord.x;
				map->piece[map->nb_point].y = n;
				map->nb_point++;
				ft_piece_realloc(map);
			}
		}
		free(line);
	}
	return (1);
}

int main(void)
{
	t_map	*map;
	char	*line;
	int		n;

	if (!(map = malloc(sizeof(t_map))))
		return (0);
	if (!(map->piece = malloc(sizeof(t_point))))
		return (0);
	n = -1;
	get_next_line(0, &line);
	if (line[10] == '1')
		map->player = 'o';
	else if (line[10] == '2')
		map->player = 'x';
	ft_get_map(map, line);
	ft_get_piece(map);
	ft_putnbr(map->piece[0].x);
	ft_putnbr(map->piece[1].x);
	ft_putnbr(map->nb_point);
	return (0);
}
