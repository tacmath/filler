/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   util.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 13:38:19 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

void	ft_free_map(t_map *map)
{
	free(map->player1);
	free(map->player2);
	free(map->path);
	mlx_destroy_image(map->mlx_ptr, map->img_ptr);
	mlx_destroy_image(map->mlx_ptr, map->filler);
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	free(map->mlx_ptr);
	free(map);
}
