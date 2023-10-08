#include "vector.h"

/*addition of two vectors*/
t_vec3	add_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3	result;

	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.z = u.z + v.z;
	return (result);
}

/*substraction of two vectors*/
t_vec3	sub_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3	result;

	result.x = u.x - v.x;
	result.y = u.y - v.y;
	result.z = u.z - v.z;
	return (result);
}

/*multiplication of each element of two vectors*/
t_vec3	mul_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3	result;

	result.x = u.x * v.x;
	result.y = u.y * v.y;
	result.z = u.z * v.z;
	return (result);
}

/*scalar multiplication of a vector*/
t_vec3	scalar_mul_vec3(double t, t_vec3 v)
{
	t_vec3	result;

	result.x = t * v.x;
	result.y = t * v.y;
	result.z = t * v.z;
	return (result);
}

/*dot product of two vectors*/
double	dot(t_vec3 u, t_vec3 v)
{
	double	result;

	result = u.x * v.x + u.y * v.y + u.z * v.z;
	return (result);
}
