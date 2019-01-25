/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 14:37:41 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 13:17:19 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef	FILLER_H
# define FILLER_H

# include "libft.h"

struct				s_point
{
	int x;
	int y;
};

typedef struct s_point t_point;

struct				s_map
{
	char			**map;
	t_point			piece_start;
	t_point			piece_len;
	t_point			*piece;
	int				nb_point;
	t_point			size;
	t_point			enemie;
	char			player;
};

typedef struct s_map t_map;

int ft_get_map(t_map *map, char *line);
int ft_fill_map(t_map *map);
int ft_get_piece(t_map *map);
int ft_check(t_map *map, int x, int y);
void ft_normalise(t_map *map);
void ft_get_piece_len(t_map *map);
void ft_free_struct(t_map *map);
void ft_resolve(t_map *map);

#endif
