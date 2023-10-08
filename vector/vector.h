#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}				t_ray;

t_vec3	add_vec3(t_vec3 u, t_vec3 v);

t_vec3	sub_vec3(t_vec3 u, t_vec3 v);

t_vec3	mul_vec3(t_vec3 u, t_vec3 v);

t_vec3	scalar_mul_vec3(double t, t_vec3 v);

double	dot(t_vec3 u, t_vec3 v);

#endif