/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 14:49:02 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 16:11:34 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

int ft_get_player(t_map *map)
{
	char	*line;

	get_next_line(0, &line);
	if (line[10] == '1')
		map->player = 'O';
	else if (line[10] == '2')
		map->player = 'X';
	free(line);
	return (1);
}

void ft_get_enemie(t_map *map)
{
	int x;
	int y;

	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
			if (map->map[y][x] == -1)
			{
				map->enemie.x = x;
				map->enemie.y = y;
				return ;
			}
	}
}

int ft_init(t_map *map)
{
	char *line;

	map->piece = 0;
	ft_get_player(map);
	get_next_line(0, &line);
	ft_get_map(map, line);
	ft_get_enemie(map);
	ft_get_piece(map);
	ft_normalise(map);
	ft_get_piece_len(map);
	ft_resolve(map);
	return (1);
}

int main(void)
{
	t_map	*map;
	char	*line;


	if (!(map = malloc(sizeof(t_map))))
		return (0);
	ft_init(map);
	while (get_next_line(0, &line) > -1)
	{
		ft_fill_map(map);
		ft_get_piece(map);
		ft_normalise(map);
		ft_get_piece_len(map);
		ft_resolve(map);
	}
	ft_free_struct(map);
	return (0);
}
