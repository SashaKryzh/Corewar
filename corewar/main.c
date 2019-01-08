/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 07:54:25 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/08 07:54:25 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		read_champ(char *file, unsigned char *champ)
{
	int		fd;
	int		ret;

	fd = open(file, O_RDONLY);
	ret = read(fd, champ, 5000);
	close(fd);
	return (ret);
}

void	puthex(uint8_t n)
{
	char	buff[2];

	if (n % 16 > 9)
		buff[1] = (n % 16 - 10 + 'a');
	else
		buff[1] = (n % 16 + '0');
	n /= 16;
	if (n % 16 > 9)
		buff[0] = (n % 16 - 10 + 'a');
	else
		buff[0] = (n % 16 + '0');
	write(1, buff, 2);
}

void	putfile(int ret, uint8_t *file)
{
	for (int j = 0; j < ret; j++)
	{
		if (j != 0 && j % 16 == 0)
			ft_printf("\n");
		puthex(file[j]);
		if (j % 2 == 1)
			ft_printf(" ");
	}
	ft_printf("\n");
}

void	check_null(uint8_t	*champ)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (champ[i] != 0)
			ft_printf("NULL ERROR");
		i++;
	}
}

void	check_magic(uint8_t *champ)
{
	int			magic;
	uint8_t		n[4];

	magic = COREWAR_EXEC_MAGIC;
	ft_memcpy(&n, champ, 4);
	if (ft_memcmp(&n, &magic, 4))
		ft_printf("MAGIC OK\n");
	else
		ft_printf("MAGIC ERROR\n");
}

void	get_name(uint8_t *champ)
{
	char	name[PROG_NAME_LENGTH + 1];
	int 	i;

	i = 0;
	while (i < PROG_NAME_LENGTH && champ[i])
	{
		name[i] = champ[i];
		i++;
	}
	name[i] = '\0';
	ft_printf("%s\n", name);
	check_null(&champ[PROG_NAME_LENGTH]);
}

void	ft_memrev(void	*s, size_t len)
{
	size_t	i;
	char	*tmpmem;
	char	tmp;

	i = 0;
	tmpmem = (char *)s;
	while (i < len / 2)
	{
		tmp = tmpmem[i];
		tmpmem[i] = tmpmem[len - i - 1];
		tmpmem[len - i - 1] = tmp;
		i++;
	}
}

void	get_size(uint8_t *champ)
{
	uint32_t	size;

	ft_memcpy(&size, champ, 4);
	ft_memrev(&size, 4);
	ft_printf("%d\n", size);
}

void	parse_players(int ac, char *av[])
{
	int				i;
	int				ret;
	uint8_t			champ[5000];

	i = 1;
	while (i < ac)
	{
		ret = read_champ(av[i], champ);
		putfile(ret, champ);
		check_magic(champ);
		get_name(&champ[4]);
		get_size(&champ[4 + PROG_NAME_LENGTH + 4]);
		i++;
	}
}

int		main(int ac, char *av[])
{
	parse_players(ac, av);
	return (0);
}
