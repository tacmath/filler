/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 13:34:41 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 15:04:48 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

int		ft_image_init(t_map *map)
{
	int trash[3];

	trash[0] = 0;
	trash[1] = 0;
	trash[2] = 0;
	map->img_ptr = mlx_new_image(map->mlx_ptr, map->size.x, map->size.y);
	map->data = (int*)mlx_get_data_addr(map->img_ptr, &trash[0], &trash[1], &trash[2]);
	map->filler = mlx_xpm_file_to_image(map->mlx_ptr, "srcs/Filler.xpm", &trash[0], &trash[1]);
	return (1);
}

char	*ft_get_one_player(char *str)
{
	int n;
	int m;
	char *player;
	
	n = ft_strlen(str);
	m = -1;
	while (str[--n] != '/')
		;
	while (str[++m + n] != '.')
		;
	player = ft_memalloc(m + 1);
	m = -1;
	while (str[++m + n] != '.')
			player[m] = str[m + n];
	player[m] = '\0';
	return (player);
}

int		ft_get_player(t_map *map)
{
	char *line;

	while (get_next_line(0, &line) > 0)
	{
		if (!ft_strncmp("$$$ exec p1 :", line, 13))
			map->player1 = ft_get_one_player(line);
		if (!ft_strncmp("$$$ exec p2 :", line, 13))
		{
			map->player2 = ft_get_one_player(line);
			free(line);
			break ;
		}
		free(line);
	}
	return (1);
}

int		ft_struct_init(t_map *map)
{
	map->size.x = LENGTH;
	map->size.y = WIDTH;
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, map->size.x, map->size.y, "filler");
	ft_image_init(map);
	map->plateau.x = 0;
	map->plateau.y = 0;
	ft_get_player(map);
	return (1);
}
