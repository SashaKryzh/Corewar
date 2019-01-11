
#include "libft.h"
#include "corewar.h"

void	putbyte_hex(uint8_t n)
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

void	putfile_hex(int ret, uint8_t *file, int space, int newline)
{
	for (int j = 0; j < ret; j++)
	{
		if (j != 0 && j % newline == 0)
			ft_printf("\n");
		putbyte_hex(file[j]);
		if (space == 1)
			ft_printf(" ");
		else if (j % space == 1)
			ft_printf(" ");
	}
	ft_printf("\n");
}

void	putbytes_bit(char *n, int size)
{
	for (int i = 0; i < size; i++)
	{
		ft_print_bits(n[i]);
		i != size - 1 ? ft_printf(" ") : ft_printf("");
	}
	ft_printf("\n");
}

void	print_players(t_player *champs)
{
	int i;

	i = 0;
	while (champs[i].id != -1)
	{
		ft_printf("%d\n", champs[i].id);
		ft_printf("%s\n", champs[i].name);
		ft_printf("%s\n", champs[i].comment);
		ft_printf("%d\n", champs[i].code_size);
		putfile_hex(champs[i].code_size, champs[i].code, 2, 16);
		i++;
		if (champs[i].id != -1)
			ft_printf("\n");
	}
}

void	print_cars(t_car *carriage)
{
	while (carriage)
	{
		ft_printf("id: %d, pos: %d, champ: %d, next: %p\n", carriage->id, carriage->position, carriage->regs[0], carriage->next);
		carriage = carriage->next;
	}
}

void	print_args_type(t_car *car)
{
	int i;

	i = 0;
	while (i < OP.args_num)
	{
		if (car->args_types[i] == (uint8_t)IND_CODE)
			ft_printf("IND ");
		if (car->args_types[i] == (uint8_t)DIR_CODE)
			ft_printf("DIR ");
		else
			ft_printf("REG ");
		i++;
	}
	ft_printf("\n");
}
