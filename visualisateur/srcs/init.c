/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 13:34:41 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 16:28:40 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

static int	ft_image_init(t_map *map)
{
	int		trash[3];
	char	*tmp;

	trash[0] = 0;
	trash[1] = 0;
	trash[2] = 0;
	if (!(map->img_ptr = mlx_new_image(map->mlx_ptr, map->size.x, map->size.y)))
		return (0);
	if (!(map->data = (int*)mlx_get_data_addr(map->img_ptr,
		&trash[0], &trash[1], &trash[2])))
		return (0);
	if (!(tmp = ft_strjoin(map->path, "srcs/Filler.xpm")))
		return (0);
	if (!(map->filler = mlx_xpm_file_to_image(map->mlx_ptr,
			tmp, &trash[0], &trash[1])))
		return (0);
	free(tmp);
	return (1);
}

static char	*ft_get_one_player(char *str)
{
	int		n;
	int		m;
	char	*player;

	n = ft_strlen(str);
	m = -1;
	while (str[--n] != '/')
		;
	while (str[++m + n] != '.')
		;
	if (!(player = ft_memalloc(m + 1)))
		return (0);
	m = -1;
	n++;
	while (str[++m + n] != '.')
		player[m] = ft_toupper(str[m + n]);
	player[m] = '\0';
	return (player);
}

static int	ft_get_player(t_map *map)
{
	char *line;

	line = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (!line)
			return (0);
		if (!ft_strncmp("$$$ exec p1 :", line, 13))
			map->player1 = ft_get_one_player(line);
		if (!ft_strncmp("$$$ exec p2 :", line, 13))
		{
			if (!(map->player2 = ft_get_one_player(line)))
				return (0);
			free(line);
			break ;
		}
		free(line);
	}
	return (1);
}

int			ft_struct_init(t_map *map)
{
	map->size.x = WIDTH;
	map->size.y = HEIGHT;
	if (!(map->mlx_ptr = mlx_init()))
		return (0);
	if (!(map->win_ptr = mlx_new_window(map->mlx_ptr,
		map->size.x, map->size.y, "filler")))
		return (0);
	if (!ft_image_init(map))
		return (0);
	map->plateau.x = 0;
	map->plateau.y = 0;
	map->p1_color = 0xFF0000;
	map->p2_color = 0x00D4FF;
	if (!ft_get_player(map))
		return (0);
	return (1);
}
