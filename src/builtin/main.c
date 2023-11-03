#include "../../inc/minishell.h"

int	main(int ac, char **av)
{
	int	i;
	char	**array;

	if (ac > 1)
	{
		array = malloc(sizeof(char *) * ac);
		i = 1;
		while (av[i - 1])
		{
			array[i] = malloc(sizeof(char) * (strlen(av[i - 1] + 1)));
			strcpy(array[i], av[i - 1]);
			i++;
		}
		echo(array);
	}
	return (0);
}
