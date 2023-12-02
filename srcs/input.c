/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 23:19:45 by jihalee           #+#    #+#             */
/*   Updated: 2023/12/02 23:19:47 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	keypress(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_window(vars);
	if (keycode == XK_w)
		vars->go_u = 1;
	else if (keycode == XK_s)
		vars->go_d = 1;
	else if (keycode == XK_d)
		vars->go_r = 1;
	else if (keycode == XK_a)
		vars->go_l = 1;
	else if (keycode == XK_Left)
		vars->rotate_ccw = 1;
	else if (keycode == XK_Right)
		vars->rotate_cw = 1;
	return (0);
}

int	keyrelease(int keycode, t_vars *vars)
{
	if (keycode == XK_w)
		vars->go_u = 0;
	else if (keycode == XK_s)
		vars->go_d = 0;
	else if (keycode == XK_d)
		vars->go_r = 0;
	else if (keycode == XK_a)
		vars->go_l = 0;
	else if (keycode == XK_Left)
		vars->rotate_ccw = 0;
	else if (keycode == XK_Right)
		vars->rotate_cw = 0;
	return (0);
}
