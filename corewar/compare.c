
#include "libft.h"
#include "fcntl.h"

int main(int ac, char **av)
{
	int fd1, fd2;
	char *l1;
	char *l2;
	int i = 1;

	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);

	while (get_next_line(fd1, &l1))
	{
		get_next_line(fd2, &l2);
		if (!ft_strequ(l1, l2))
		{
			ft_printf("error: %s (%d)\n", l1, i);
		}
		else if (i % 10000 == 0)
			ft_printf("%d\n", i);
		i++;
	}
}