/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 14:49:02 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 14:31:02 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

static int	ft_get_player(t_map *map)
{
	char *line;

	if (get_next_line(0, &line) < 1)
		return (0);
	if (ft_strncmp(line, "$$$ exec p", 10))
		return (0);
	if (line[10] == '1')
		map->player = 'O';
	else if (line[10] == '2')
		map->player = 'X';
	free(line);
	return (1);
}

static void	ft_get_enemie(t_map *map)
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

static int	ft_init(t_map *map)
{
	char	*line;
	int		status;

	line = 0;
	map->piece = 0;
	if (!ft_get_player(map))
		return (0);
	while ((status = get_next_line(0, &line)) > 0)
	{
		if (line && !ft_strncmp("Plateau", line, 7))
		{
			if (!ft_get_map(map, line))
				return (0);
			ft_get_enemie(map);
			if (get_next_line(0, &line) < 1)
				return (0);
			if (!ft_get_piece(map, ft_atoi(&(line[5]))))
				return (0);
			free(line);
			return (1);
		}
		ft_memdel((void**)&line);
	}
	if (status == -1)
		return (0);
	return (1);
}

int			main(void)
{
	t_map	*map;
	char	*line;
	int		n;

	line = 0;
	n = 0;
	if (!(map = malloc(sizeof(t_map))))
		return (0);
	if (ft_init(map) < 1)
		return (0);
	while (get_next_line(0, &line) > 0)
	{
		if (line && !ft_strncmp("Plateau", line, 7))
			if (!ft_fill_map(map))
				return (0);
		ft_memdel((void**)&line);
	}
	ft_free_struct(map);
	return (0);
}
