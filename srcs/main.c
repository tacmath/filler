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
	while (!ft_strstr(line, "mtaquet.filler"))
	{
		free(line);
		get_next_line(0, &line);
	}
	if (line[10] == '1')
		map->player = 'O';
	else if (line[10] == '2')
		map->player = 'X';
	free(line);
}

int main(void)
{
	t_map	*map;
	char	*line;

	if (!(map = malloc(sizeof(t_map))))
		return (0);
	map->piece = 0;
	ft_get_player(map);
	get_next_line(0, &line);
	ft_get_map(map, line);
	ft_get_piece(map);
	ft_normalise(map);
	ft_get_piece_len(map);
	ft_free_struct(map);
	return (0);
}
