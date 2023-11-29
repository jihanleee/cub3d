

int flood_fill(t_vars *vars)
{
	char	**copy;
	int		i;

	//create map copy
	copy = (char **)malloc(sizeof(char *) * (vars->height + 1));
	i = 0;
	while (i < vars->height)
	{
		copy[i] = (char *)malloc(sizeof(char) * (vars->width + 1));
		if (!copy[i])
		{
			//free_map(copy);
			exit_error("ERROR - Malloc Error");
		}
		i++;
	}
	//copy contents to map copy


	//flood fill
		//fail ==> free, exit

	
	//success ==> free
}