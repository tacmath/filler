/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 14:49:02 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/27 14:51:31 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

int ft_get_player(t_map *map)
{
	char	*line;

	get_next_line(0, &line);
	if (ft_strncmp(line, "$$$ exec p", 10))
		return (0);

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

void ft_put_map_fd(t_map *map)
{
	int x;
	int y;
	int fd;

	fd = open("test.txt", O_WRONLY | O_CREAT, 777);
	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
			ft_putnbr_fd(map->map[y][x], fd);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
}

void ft_put_piece_fd(t_map *map)
{
	int fd;
	int n;

	n = -1;
	fd = open("test.txt", O_WRONLY | O_CREAT, 777);
	ft_putnbr_fd(map->nb_point, fd);
	ft_putchar_fd('\n', fd);
	while (++n < map->nb_point)
	{
		ft_putnbr_fd(map->piece[n].x, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map->piece[n].y, fd);
		ft_putchar_fd('\n', fd);
	}
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(map->enemie.x, fd);
	ft_putnbr_fd(map->enemie.y, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}

int ft_init(t_map *map)
{
	char *line;

	line = 0;
	map->piece = 0;
	ft_get_player(map);
	while (get_next_line(0, &line) > -1)
	{
		if (line && !ft_strncmp("Plateau", line, 7))
		{
			ft_get_map(map, line);
			ft_get_enemie(map);
	//	}
	//	else if (line && !ft_strncmp("Piece", line, 5))
	//	{
		//	get_next_line(0, &line);
			ft_get_piece(map);
			break ;
		}
		ft_memdel((void**)&line);
	}
	return (1);
}

int main(void)
{
	t_map	*map;
	char	*line;
	int n;

	line = 0;
	n = 0;
	if (!(map = malloc(sizeof(t_map))))
		return (0);
	ft_init(map);
	while (get_next_line(0, &line) > -1)
	{
		if (line && !ft_strncmp("Plateau", line, 7))
		{
			ft_fill_map(map);
		//else if (line && !ft_strncmp("Piece", line, 5))
		//{
		//	get_next_line(0, &line);
		}
		ft_memdel((void**)&line);
	}
	ft_free_struct(map);
	return (0);
}
