/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 23:19:58 by jihalee           #+#    #+#             */
/*   Updated: 2023/12/03 00:52:18 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_vars *vars)
{
	double	x;
	double	y;

	if (!vars->rotate_cw && !vars->rotate_ccw)
		return ;
	if (vars->rotate_ccw)
		vars->current_angle = (vars->current_angle + ROT_SPEED);
	if (vars->rotate_cw)
		vars->current_angle = (vars->current_angle - ROT_SPEED);
	if (vars->current_angle > M_PI * 2)
		vars->current_angle -= (M_PI * 2);
	if (vars->current_angle < 0)
		vars->current_angle += (M_PI * 2);
	x = vars->init_dir_x;
	y = vars->init_dir_y;
	vars->dir_x = x * cos(vars->current_angle) - y * sin(vars->current_angle);
	vars->dir_y = x * sin(vars->current_angle) + y * cos(vars->current_angle);
	x = vars->init_dir_y * 0.66;
	y = -vars->init_dir_x * 0.66;
	vars->plane_x = x * cos(vars->current_angle) - y * sin(vars->current_angle);
	vars->plane_y = x * sin(vars->current_angle) + y * cos(vars->current_angle);
	vars->rinfo.raydir_x = vars->dir_x;
	vars->rinfo.raydir_y = vars->dir_y;
}

static void	apply_move(t_vars *vars, double delta_x, double delta_y)
{
	int	current_x_index;
	int	current_y_index;
	int	next_x_index;
	int	next_y_index;

	current_x_index = (int)vars->player_x;
	current_y_index = (int)vars->player_y;
	next_x_index = (int)(vars->player_x + delta_x);
	next_y_index = (int)(vars->player_y + delta_y);
	if (vars->map[current_y_index][next_x_index] != '1')
		vars->player_x += delta_x;
	if (vars->map[next_y_index][current_x_index] != '1')
		vars->player_y += delta_y;
}

void	move(t_vars *vars)
{
	if (vars->go_u)
		apply_move(vars, MOVE_SPEED * vars->dir_x, MOVE_SPEED * vars->dir_y);
	if (vars->go_d)
		apply_move(vars, -MOVE_SPEED * vars->dir_x, -MOVE_SPEED * vars->dir_y);
	if (vars->go_r)
		apply_move(vars, MOVE_SPEED * vars->dir_y, -MOVE_SPEED * vars->dir_x);
	if (vars->go_l)
		apply_move(vars, -MOVE_SPEED * vars->dir_y, MOVE_SPEED * vars->dir_x);
}
