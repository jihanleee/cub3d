/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 23:19:00 by jihalee           #+#    #+#             */
/*   Updated: 2023/12/18 18:30:18 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_iteration(t_vars *vars, int x);
static int	get_w_dir(t_vars *vars);
static void	draw_iteration(t_vars *vars, int x);

static int	get_w_dir(t_vars *vars)
{
	int		w_dir;

	if (vars->rinfo.side == 1 && vars->rinfo.raydir_y > 0)
		w_dir = SOUTH;
	if (vars->rinfo.side == 1 && vars->rinfo.raydir_y < 0)
		w_dir = NORTH;
	if (vars->rinfo.side == 0 && vars->rinfo.raydir_x > 0)
		w_dir = WEST;
	if (vars->rinfo.side == 0 && vars->rinfo.raydir_x < 0)
		w_dir = EAST;
	return (w_dir);
}

static void	get_lineinfo(t_vars *vars)
{
	if (vars->rinfo.side == 0)
		vars->rinfo.wall_x = \
		vars->player_y + vars->rinfo.perpwalldist * vars->rinfo.raydir_y;
	else
		vars->rinfo.wall_x = \
		vars->player_x + vars->rinfo.perpwalldist * vars->rinfo.raydir_x;
	vars->rinfo.wall_x -= floor(vars->rinfo.wall_x);
	vars->rinfo.tex_x = (int)(vars->rinfo.wall_x * (double)(128));
	vars->rinfo.lineheight = (int)(IMG_HEIGHT / vars->rinfo.perpwalldist);
	vars->rinfo.drawstart = -vars->rinfo.lineheight / 2 + IMG_HEIGHT / 2;
	vars->rinfo.drawn_len = 0;
	if (vars->rinfo.drawstart < 0)
	{
		vars->rinfo.drawn_len = abs(vars->rinfo.drawstart);
		vars->rinfo.drawstart = 0;
	}
	vars->rinfo.drawend = vars->rinfo.lineheight / 2 + IMG_HEIGHT / 2;
	if (vars->rinfo.drawend >= IMG_HEIGHT)
		vars->rinfo.drawend = IMG_HEIGHT - 1;
}

static void	draw_iteration(t_vars *vars, int x)
{
	int	y;

	y = 0;
	while (y < IMG_HEIGHT)
	{
		vars->rinfo.tex_y = \
		(int)((double)vars->rinfo.drawn_len / \
		(double)vars->rinfo.lineheight * (double)(128));
		if (y >= vars->rinfo.drawstart && y < vars->rinfo.drawend)
		{
			my_mlx_pixel_put(&(vars->wimg), x, y, \
			pixel_color(&(vars->tex[get_w_dir(vars)]), \
			vars->rinfo.tex_x, vars->rinfo.tex_y));
			vars->rinfo.drawn_len++;
		}
		else if (y < IMG_HEIGHT / 2)
			my_mlx_pixel_put(&(vars->wimg), x, y, vars->c_colour);
		else
			my_mlx_pixel_put(&(vars->wimg), x, y, vars->f_colour);
		y++;
	}
}

void	draw_line(t_vars *vars, int x)
{
	get_lineinfo(vars);
	draw_iteration(vars, x);
}
