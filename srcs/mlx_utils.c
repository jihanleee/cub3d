/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 23:19:12 by jihalee           #+#    #+#             */
/*   Updated: 2023/12/03 01:36:08 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	initialize_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	save_texture(vars);
	vars->win = mlx_new_window(vars->mlx, IMG_WIDTH, IMG_HEIGHT, "cub3d");
	vars->img.img = mlx_new_image(vars->mlx, IMG_WIDTH, IMG_HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bits_per_pixel,
			&vars->img.line_length,
			&vars->img.endian);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > IMG_WIDTH || y > IMG_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	pixel_color(t_data *data, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x > IMG_WIDTH || y > IMG_HEIGHT)
		return (0);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
