/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayalee <mayalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:01:19 by jihalee           #+#    #+#             */
/*   Updated: 2023/11/27 23:09:57 by mayalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <mlx_int.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef __USE_MISC
#  define __USE_MISC
# endif
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

# define IMG_WIDTH 256
# define IMG_HEGIHT 256
# define MOVE_SPEED 0.1
//add ROT_SPEED

typedef struct s_data //for image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars //info
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_data		img;
	bool		key_pressed;
	char		**map;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_vars;

//parsing
/*
- 사이즈 받아두기
- 빈칸 X로 채워서 map validity check
- X는 맵 그리는 과정에서 0이나 1로 취급
*/

#endif
