#include <stdio.h>
#include "minirt.h"

int	initialize_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, IMG_WIDTH, IMG_HEGIHT, "fdf");
	vars->img.img = mlx_new_image(vars->mlx, IMG_WIDTH, IMG_HEGIHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bits_per_pixel,
			&vars->img.line_length,
			&vars->img.endian);
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

/*closes the window when esc is pressed*/
int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_window(vars);
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

int	main()
{
	t_vars	vars;
	int		i;
	int		j;

	initialize_vars(&vars);
	j = 0;
	while (j++ < IMG_HEGIHT)
	{
		i = 0;
		while (i++ < IMG_WIDTH)
			my_mlx_pixel_put(&vars.img, i, j, (i << 16) + (j << 8) + 0);
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
