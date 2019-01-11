/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 14:37:41 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/11 14:50:42 by mtaquet     ###    #+. /#+    ###.fr     */
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
	t_point			size;
	char			player;
};

typedef struct s_map t_map;


#endif
