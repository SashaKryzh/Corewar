
#include "libft.h"
#include "corewar.h"

void	print_players(t_player *champs)
{
	int i;

	i = 0;
	ft_printf("\n");
	while (champs[i].id != -1)
	{
		ft_printf("%d\n", champs[i].id);
		ft_printf("%s\n", champs[i].name);
		ft_printf("%s\n", champs[i].comment);
		ft_printf("%d\n", champs[i].code_size);
		putfile(champs[i].code_size, champs[i].code);
		i++;
		if (champs[i].id != -1)
			ft_printf("\n");
	}
}
