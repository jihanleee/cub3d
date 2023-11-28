void	exit_error(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	//exit(EXIT_FAILURE);
}