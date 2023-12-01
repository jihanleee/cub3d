#include <stdio.h>
#include "cub3d.h"

int	initialize_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, IMG_WIDTH, IMG_HEIGHT, "cub3d");
	vars->img.img = mlx_new_image(vars->mlx, IMG_WIDTH, IMG_HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bits_per_pixel,
			&vars->img.line_length,
			&vars->img.endian);
	//vars->img.bits_per_pixel = 0;
	//vars->img.line_length = 0;
	//vars->img.endian = 0;
	vars->go_u = 0;
	vars->go_d = 0;
	vars->go_l = 0;
	vars->go_r = 0;
	vars->rotate_cw = 0;
	vars->rotate_ccw = 0;
	vars->current_angle = 0;
	vars->start_x = 0;
	vars->start_y = 0;
	vars->dir_x = 0;
	vars->dir_y = -1; /*initial direction*/	
	vars->plane_x = -0.66;
	vars->plane_y = 0; /*camera plane of FOV 90*/
	//added below
	vars->map = NULL;
	vars->player_x = 1.5;
	vars->player_y = 1.5;
	vars->players = 0;
	vars->height = 0;
	vars->width = 0;
	vars->f_colour = 0;
	vars->c_colour = 0;
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

int	keypress(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_window(vars);
	ft_printf("keypress %d\n", keycode);
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
	printf("plane x %f plane y %f\n", vars->plane_x, vars->plane_y);
	vars->rinfo.raydir_x = vars->dir_x;
	vars->rinfo.raydir_y = vars->dir_y;
	get_dist(vars);
	printf("distance :%f", vars->rinfo.perpwalldist);
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

void	shoot_rays(t_vars *vars)
{
	int	x;
	double camera_x;

	vars->wimg.img = mlx_new_image(vars->mlx, IMG_WIDTH, IMG_HEIGHT);
	vars->wimg.addr = mlx_get_data_addr(vars->wimg.img,
			&vars->wimg.bits_per_pixel,
			&vars->wimg.line_length,
			&vars->wimg.endian);
	x = 0;
	while(x < IMG_WIDTH)
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

void	draw_line(t_vars *vars, int x)
{
	int	lineheight;
	int	drawstart;
	int	drawend;
	int	y;
	int	i;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		w_dir;

	if (vars->rinfo.side == 1 && vars->rinfo.raydir_y > 0)
		w_dir = 0;
	if (vars->rinfo.side == 1 && vars->rinfo.raydir_y < 0)
		w_dir = 1;
	if (vars->rinfo.side == 0 && vars->rinfo.raydir_x > 0)
		w_dir = 2;
	if (vars->rinfo.side == 0 && vars->rinfo.raydir_x < 0)
		w_dir = 3;
	if (vars->rinfo.side == 0)
		wall_x = vars->player_y + vars->rinfo.perpwalldist * vars->rinfo.raydir_y;
	else
		wall_x = vars->player_x + vars->rinfo.perpwalldist * vars->rinfo.raydir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)(128));
    lineheight = (int)(IMG_HEIGHT / vars->rinfo.perpwalldist);
    drawstart = -lineheight / 2 + IMG_HEIGHT / 2;
    drawend = lineheight / 2 + IMG_HEIGHT / 2;
	y = drawstart;
	i = 0;
	while (y < drawend)
	{
		tex_y = (int)((double)i / (double)lineheight * (double)(128));
		my_mlx_pixel_put(&(vars->wimg), x, y, pixel_color(&(vars->tex[w_dir]), tex_x, tex_y));
		i++;
		y++;
	}
}

int	render_next_frame(t_vars *vars)
{
	move(vars);
	rotate(vars);
	shoot_rays(vars);
	return (0);
}

double  get_dist(t_vars *vars)
{
	vars->rinfo.map_x = (int)vars->player_x;
	vars->rinfo.map_y = (int)vars->player_y;
    if (vars->rinfo.raydir_x == 0)
        vars->rinfo.deltadist_x = 9999999;
    else
        vars->rinfo.deltadist_x = fabs(1 / vars->rinfo.raydir_x);
    if (vars->rinfo.raydir_y == 0)
        vars->rinfo.deltadist_y = 9999999;
    else
       vars->rinfo.deltadist_y = fabs(1 / vars->rinfo.raydir_y);
    vars->rinfo.hit = 0;
    if (vars->rinfo.raydir_x < 0)
    {
        vars->rinfo.step_x = -1;
        vars->rinfo.sidedist_x = (vars->player_x - vars->rinfo.map_x) * vars->rinfo.deltadist_x;
    }
    else
    {
        vars->rinfo.step_x = 1;
        vars->rinfo.sidedist_x = (vars->rinfo.map_x + 1.0 - vars->player_x) * vars->rinfo.deltadist_x;
    }
    if (vars->rinfo.raydir_y < 0)
    {
        vars->rinfo.step_y = -1;
       vars->rinfo.sidedist_y = (vars->player_y - vars->rinfo.map_y) * vars->rinfo.deltadist_y;
    }
    else
    {
        vars->rinfo.step_y = 1;
        vars->rinfo.sidedist_y = (vars->rinfo.map_y + 1.0 - vars->player_y) * vars->rinfo.deltadist_y;
    }
    while (vars->rinfo.hit == 0)
    {
        if (vars->rinfo.sidedist_x < vars->rinfo.sidedist_y)
        {
            vars->rinfo.sidedist_x += vars->rinfo.deltadist_x;
            vars->rinfo.map_x += vars->rinfo.step_x;
            vars->rinfo.side = 0;
        }
        else
        {
            vars->rinfo.sidedist_y += vars->rinfo.deltadist_y;
           vars->rinfo. map_y += vars->rinfo.step_y;
        	vars->rinfo.side = 1;
        }
        if (vars->map[vars->rinfo.map_y][vars->rinfo.map_x] == '1')
            vars->rinfo.hit = 1;
    }
    if(vars->rinfo.side == 0)
		vars->rinfo.perpwalldist = (vars->rinfo.sidedist_x - vars->rinfo.deltadist_x);
    else
		vars->rinfo.perpwalldist = (vars->rinfo.sidedist_y - vars->rinfo.deltadist_y);
}


/*texture test module*/
/* int	main(int argc, char **argv)
{
	t_vars	vars;
	int		i;
	int		j;

	vars.file = argv[1];
	initialize_vars(&vars);
	j = 0;
	vars.texture.img = mlx_xpm_file_to_image(vars.mlx, "pigsmall.xpm", &i, &j);
	vars.texture.addr = mlx_get_data_addr(vars.texture.img,
			&vars.texture.bits_per_pixel,
			&vars.texture.line_length,
			&vars.texture.endian);
	j = 0;
	while (j++ < 256)
	{
		i = 0;
		while (i++ < 256)
			my_mlx_pixel_put(&vars.img, i, j, pixel_color(&vars.texture, i / 2, j / 2));
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
} */

void	save_texture(t_vars *vars)
{
	int		index;
	char	*line;
	char	**array;
	int		fd;
	int		i;
	int		j;

	index = 0;
	fd = open(vars->file, O_RDONLY);
	line = get_next_line(fd);
	while (index < 4)
	{
		array = ft_split(line, ' ');
		vars->tex[index].img = mlx_xpm_file_to_image(vars->mlx, array[1], &i, &j);
		printf("here\n");
		printf("file: %s\n", array[1]);
		vars->tex[index].addr = mlx_get_data_addr(&(vars->tex[index].img), \
			&(vars->tex[index].bits_per_pixel), \
			&(vars->tex[index].line_length), \
			&(vars->tex[index].endian));
		printf("here2\n");
		free(array[1]);
		free(array[0]);
		free(array);
		free(line);
		line = get_next_line(fd);
		index++;
	}
}	
int	main(int argc, char **argv)
{
	t_vars	vars;
/* 	int		i;
	int		j; */

	if (argc != 2)
		return (1);
	vars.file = argv[1];
	initialize_vars(&vars);
	validate_file(&vars);
	/* save_texture(&vars); */
	print_maps(vars.first_map, &vars);//
	printf("f-colour: %u\n", vars.f_colour);
	printf("c-colour: %u\n", vars.c_colour);
	if (validate_map(&vars) == 1)
	{
		exit_error("ERROR - Invalid Map");
		return (1);
	}
	//print_maps(vars.map, &vars);//
	save_texture(&vars);

/* 	vars.tex[0].img = mlx_xpm_file_to_image(vars.mlx, "texture_1.xpm", &i, &j);
	vars.tex[0].addr = mlx_get_data_addr(vars.tex[0].img,
			&vars.tex[0].bits_per_pixel,
			&vars.tex[0].line_length,
			&vars.tex[0].endian);
	vars.tex[1].img = mlx_xpm_file_to_image(vars.mlx, "texture_2.xpm", &i, &j);
	vars.tex[1].addr = mlx_get_data_addr(vars.tex[1].img,
			&vars.tex[1].bits_per_pixel,
			&vars.tex[1].line_length,
			&vars.tex[1].endian);
	vars.tex[2].img = mlx_xpm_file_to_image(vars.mlx, "texture_3.xpm", &i, &j);
	vars.tex[2].addr = mlx_get_data_addr(vars.tex[2].img,
			&vars.tex[2].bits_per_pixel,
			&vars.tex[2].line_length,
			&vars.tex[2].endian);
	vars.tex[3].img = mlx_xpm_file_to_image(vars.mlx, "texture_4.xpm", &i, &j);
	vars.tex[3].addr = mlx_get_data_addr(vars.tex[3].img,
			&vars.tex[3].bits_per_pixel,
			&vars.tex[3].line_length,
			&vars.tex[3].endian);
 */

	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
	mlx_hook(vars.win, 02, 1L << 0, keypress, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 03, 1L << 1, keyrelease, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
