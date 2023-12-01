/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maya <maya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/01 16:19:11 by maya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define XK_a                             0x0061  /* U+0061 LATIN SMALL LETTER A */
#define XK_b                             0x0062  /* U+0062 LATIN SMALL LETTER B */
#define XK_c                             0x0063  /* U+0063 LATIN SMALL LETTER C */
#define XK_d                             0x0064  /* U+0064 LATIN SMALL LETTER D */
#define XK_e                             0x0065  /* U+0065 LATIN SMALL LETTER E */
#define XK_f                             0x0066  /* U+0066 LATIN SMALL LETTER F */
#define XK_g                             0x0067  /* U+0067 LATIN SMALL LETTER G */
#define XK_h                             0x0068  /* U+0068 LATIN SMALL LETTER H */
#define XK_i                             0x0069  /* U+0069 LATIN SMALL LETTER I */
#define XK_j                             0x006a  /* U+006A LATIN SMALL LETTER J */
#define XK_k                             0x006b  /* U+006B LATIN SMALL LETTER K */
#define XK_l                             0x006c  /* U+006C LATIN SMALL LETTER L */
#define XK_m                             0x006d  /* U+006D LATIN SMALL LETTER M */
#define XK_n                             0x006e  /* U+006E LATIN SMALL LETTER N */
#define XK_o                             0x006f  /* U+006F LATIN SMALL LETTER O */
#define XK_p                             0x0070  /* U+0070 LATIN SMALL LETTER P */
#define XK_q                             0x0071  /* U+0071 LATIN SMALL LETTER Q */
#define XK_r                             0x0072  /* U+0072 LATIN SMALL LETTER R */
#define XK_s                             0x0073  /* U+0073 LATIN SMALL LETTER S */
#define XK_t                             0x0074  /* U+0074 LATIN SMALL LETTER T */
#define XK_u                             0x0075  /* U+0075 LATIN SMALL LETTER U */
#define XK_v                             0x0076  /* U+0076 LATIN SMALL LETTER V */
#define XK_w                             0x0077  /* U+0077 LATIN SMALL LETTER W */
#define XK_x                             0x0078  /* U+0078 LATIN SMALL LETTER X */
#define XK_y                             0x0079  /* U+0079 LATIN SMALL LETTER Y */
#define XK_z                             0x007a  /* U+007A LATIN SMALL LETTER Z */

#define XK_Left                          0xff51  /* Move left, left arrow */
#define XK_Up                            0xff52  /* Move up, up arrow */
#define XK_Right                         0xff53  /* Move right, right arrow */
#define XK_Down                          0xff54  /* Move down, down arrow */

# define IMG_WIDTH 720
# define IMG_HEIGHT 480
# define MOVE_SPEED 0.001
# define ROT_SPEED 0.001

typedef struct s_data //for image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_rinfo
{
	int     map_x;
    int     map_y;
    double  sidedist_x;
    double  sidedist_y;
    double  deltadist_x;
    double  deltadist_y;
    double  perpwalldist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
	double	raydir_x;
	double	raydir_y;
}				t_rinfo;

typedef struct s_vars //info
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_data		img;
	t_data		wimg;
	t_data		tex[4];
	bool		key_pressed;
	char		*file;
	char		**first_map;
	char		**map;
	int			go_u;
	int			go_d;
	int			go_r;
	int			go_l;
	int			rotate_cw;
	int			rotate_ccw;
	double		current_angle;
	int			height;
	int			width;
	int			players;
	double		player_x;
	double		player_y;
	int			start_x;
	int			start_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	unsigned int	f_colour;
	unsigned int	c_colour;
	t_rinfo		rinfo;
}				t_vars;

/* validate_file.c */
void	add_to_map(t_vars *vars, int count);
void	validate_file(t_vars *vars);

/* validate_map.c */
void	parse_map(t_vars *vars);
int		validate_map(t_vars *vars);

/* utils.c */
void	exit_error(char *message);
//void	print_maps(char **map);
void	print_maps(char **map, t_vars *vars);

/* flood_fill.c */
int flood_fill(t_vars *vars);

/*main.c*/
double  get_dist(t_vars *vars);
void	draw_line(t_vars *vars, int x);
#endif
