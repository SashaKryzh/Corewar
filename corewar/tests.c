
#include "libft.h"
#include "corewar.h"

void	print_players(t_player *champs)
{
	int i;

	i = 0;
	while (champs[i].id != -1)
	{
		ft_printf("%s\n", champs->name);
		ft_printf("%s\n", champs->comment);
		ft_printf("%d\n", champs->code_size);
		i++;
	}
}
