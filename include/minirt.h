/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:01:19 by jihalee           #+#    #+#             */
/*   Updated: 2023/10/08 23:34:36 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
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
# include "libft.h"
# include "vector.h"

# define IMG_WIDTH 256
# define IMG_HEGIHT 256

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_data		img;
	int			need_update;
}				t_vars;

#endif
