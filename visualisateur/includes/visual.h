/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visual.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 14:37:32 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 16:57:41 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H
# include "libft.h"
# include "mlx.h"
# define TRUE				1
# define FALSE				0
# define WIDTH				1000
# define HEIGHT				900
# define KEY_PRESS			2
# define BUTTON_RELEASE		5
# define MOTION_NOTIFY		6
# define DESTROY_NOTIFY		17
# define KEY_ESCAPE			53

struct					s_point
{
	int					x;
	int					y;
};

typedef struct s_point	t_point;

struct					s_map
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	void				*filler;
	int					*data;
	char				*player1;
	char				*player2;
	char				*path;
	int					p1_point;
	int					p2_point;
	int					p1_color;
	int					p2_color;
	int					pix_len;
	t_point				start;
	t_point				plateau;
	t_point				size;
};

typedef struct s_map	t_map;

int						ft_destroy(t_map *map);
void					ft_get_len_plateau(t_map *map, char *line);
int						deal_key(int key, t_map *map);
void					ft_free_map(t_map *map);
int						ft_struct_init(t_map *map);
void					ft_put_point(t_map *map, int x, int y, int color);
void					ft_draw(t_map *map);

#endif
