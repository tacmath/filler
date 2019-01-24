#include "filler.h"

int ft_check_enemie_co(t_map *map, int x, int y)
{
	int co;
	int n;

	co = 0;
	n = -1;
	while (++n < map->nb_piece)
	{
		if (x > 0 && map->map[map->piece[n].x + x - 1] = -1)
			co++;
		if (x < map->size.x && map->map[map->piece[n].x + x + 1] = -1)
			co++;
		if (y > 0 && map->map[map->piece[n].y + y - 1] = -1)
			co++;
		if (y < map->size.x && map->map[map->piece[n].y + y + 1] = -1)
			co++;		
	}
	return (co);
}

void ft_resol(t_map *map)
{
	int x;
	int y;
	t_point place;
	int co_enemie;

	co_enemie = -1;
	place.x = 0;
	place.y = 0;
	y = -1;
	while (++y < map->size.y - map->piece_len.y)
	{
		x = -1;
		while (++x < map->size.x - map->piece_len.x)
			if (ft_check(map, x, y))
				if (co_enemie < ft_check_enemie_co(map, x, y))
				{
					co_enemie = ft_check_enemie_co(map, x, y);
					place.x = x;
					place.y = y;
				}
	}
	ft_putnbr(place.x - map->piece_start.x);
	ft_putchar(' ');
	ft_putnbr(place.y - map->piece_start.y);
	ft_putchar('\n');
}
