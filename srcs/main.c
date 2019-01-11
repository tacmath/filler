/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 14:49:02 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/11 14:49:53 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

int main(void)
{
	t_map	*map;
	char	*line;
	int		n;

	if (!(map = malloc(sizeof(t_map))))
		return (0);
	n = -1;
	get_next_line(0, &line);
	if (line[10] == '1')
		map->player = 'o';
	else if (line[10] == '2')
		map->player = 'x';
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
	return (0);
}
