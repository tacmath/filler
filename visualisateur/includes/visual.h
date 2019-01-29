/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visual.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 14:37:32 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 14:50:47 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H
# include "libft.h"
# include "mlx.h"
# define TRUE				1
# define FALSE				0
# define LENGTH				1300
# define WIDTH				900
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
	int					p1_point;
	int					p2_point;
	int					pix_len;
	t_point				start;
	t_point				plateau;
	t_point				size;
};

typedef struct s_map	t_map;

int						ft_destroy(t_map *map);
int						deal_key(int key, t_map *map);
void					ft_free_map(t_map *map);
int						ft_struct_init(t_map *map);

#endif
