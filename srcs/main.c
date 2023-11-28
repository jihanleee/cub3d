#include <stdio.h>
#include "cub3d.h"

int	initialize_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, IMG_WIDTH, IMG_HEGIHT, "fdf");
	vars->img.img = mlx_new_image(vars->mlx, IMG_WIDTH, IMG_HEGIHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bits_per_pixel,
			&vars->img.line_length,
			&vars->img.endian);
	vars->go_u = 0;
	vars->go_d = 0;
	vars->go_l = 0;
	vars->go_r = 0;
	vars->rotate_cw = 0;
	vars->rotate_ccw = 0;
	vars->current_angle = 0;
	vars->player_x = 22;
	vars->player_y = 33; /*initial position*/
	//vars->player_x = 0;
	//vars->player_y = 0;
	vars->dir_x = 0;
	vars->dir_y = -1; /*initial direction*/
	vars->plane_x = 0;
	vars->plane_y = 0.66; /*camera plane of FOV 90*/
	//added below
	vars->map = NULL;
	vars->player_x = 0;
	vars->player_y = 0;
	vars->players = 0;
	vars->height = 0;
	vars->width = 0;
	return (0);
}

/*closes the windown when cross button 
on the top-right corner is clicked.*/
int	close_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > IMG_WIDTH || y > IMG_HEGIHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	keypress(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_window(vars);
	ft_printf("keypress %d\n", keycode);
	if (keycode == XK_w)
		vars->go_u = 1;
	else if (keycode == XK_s)
		vars->go_d = 1;
	else if (keycode == XK_a)
		vars->go_r = 1;
	else if (keycode == XK_d)
		vars->go_l = 1;
	else if (keycode == XK_Left)
		vars->rotate_cw = 1;
	else if (keycode == XK_Right)
		vars->rotate_ccw = 1;
	return (0);
}

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
	x = 0;
	y = -1;
	vars->dir_x = x * cos(vars->current_angle) - y * sin(vars->current_angle);
	vars->dir_y = x * sin(vars->current_angle) + y * cos(vars->current_angle);
	x = -0.66;
	y = 0;
	vars->plane_x = x * cos(vars->current_angle) - y * sin(vars->current_angle);
	vars->plane_y = x * sin(vars->current_angle) + y * cos(vars->current_angle);
	printf("current angle %f dir_x %f dir_y %f\n", vars->current_angle, vars->dir_x, vars->dir_y);
}

void	move(t_vars *vars)
{
	if (vars->go_u)
	{
			vars->player_x += MOVE_SPEED * vars->dir_x;
			vars->player_y += MOVE_SPEED * vars->dir_y;
		printf("%f %f\n", vars->player_x, vars->player_y);
		my_mlx_pixel_put(&(vars->img), vars->player_x, vars->player_y, 0x00ffffff);
	}
	if (vars->go_d)
	{
			vars->player_x -= MOVE_SPEED * vars->dir_x;
			vars->player_y -= MOVE_SPEED * vars->dir_y;
		printf("%f %f\n", vars->player_x, vars->player_y);
		my_mlx_pixel_put(&(vars->img), vars->player_x, vars->player_y, 0x00ffffff);
	}
	if (vars->go_r)
	{
		vars->player_x += MOVE_SPEED * vars->dir_y;
		vars->player_y -= MOVE_SPEED * vars->dir_x;
		printf("%f %f\n", vars->player_x, vars->player_y);
		my_mlx_pixel_put(&(vars->img), vars->player_x, vars->player_y, 0x00ffffff);
	}
	if (vars->go_l)
	{
		vars->player_x -= MOVE_SPEED * vars->dir_y;
		vars->player_y += MOVE_SPEED * vars->dir_x;
		printf("%f %f\n", vars->player_x, vars->player_y);
		my_mlx_pixel_put(&(vars->img), vars->player_x, vars->player_y, 0x00ffffff);
	}
}

int	keyrelease(int keycode, t_vars *vars)
{
	ft_printf("keyrelease\n");
	if (keycode == XK_w)
		vars->go_u = 0;
	else if (keycode == XK_s)
		vars->go_d = 0;
	else if (keycode == XK_a)
		vars->go_r = 0;
	else if (keycode == XK_d)
		vars->go_l = 0;
	else if (keycode == XK_Left)
		vars->rotate_cw = 0;
	else if (keycode == XK_Right)
		vars->rotate_ccw = 0;
	return (0);
}

int	render_next_frame(t_vars *vars)
{
	move(vars);
	rotate(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		i;
	int		j;

	if (argc != 2)
		return (1);
	vars.file = argv[1];
	initialize_vars(&vars);
	validate_file(&vars);
	print_maps(vars.first_map, &vars);//
	validate_map(&vars);
	print_maps(vars.map, &vars);//
	j = 0;
	while (j++ < IMG_HEGIHT)
	{
		i = 0;
		while (i++ < IMG_WIDTH)
			my_mlx_pixel_put(&vars.img, i, j, (i << 16) + (j << 8) + 0);
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
	mlx_hook(vars.win, 02, 1L << 0, keypress, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 03, 1L << 1, keyrelease, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
