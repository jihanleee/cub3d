/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 23:16:17 by jihalee           #+#    #+#             */
/*   Updated: 2023/12/02 23:17:04 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_vars *vars)
{
	int		x;
	double	camera_x;

	vars->wimg.img = mlx_new_image(vars->mlx, IMG_WIDTH, IMG_HEIGHT);
	vars->wimg.addr = mlx_get_data_addr(vars->wimg.img,
			&vars->wimg.bits_per_pixel,
			&vars->wimg.line_length,
			&vars->wimg.endian);
	x = 0;
	while (x < IMG_WIDTH)
	{
		camera_x = 2 * x / (double)IMG_WIDTH - 1;
		vars->rinfo.raydir_x = vars->dir_x + vars->plane_x * camera_x;
		vars->rinfo.raydir_y = vars->dir_y + vars->plane_y * camera_x;
		get_dist(vars);
		draw_line(vars, x);
		x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->wimg.img, 0, 0);
	mlx_destroy_image(vars->mlx, vars->wimg.img);
}
