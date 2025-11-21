#include "../../../headers/cube3D.h"

void	copy_chars(int *i, int *j, char **copy_tab, char **tab)
{
	while (*j < ft_strlen(tab[*i]))
	{
		copy_tab[*i][*j] = tab[*i][*j];
		(*j)++;
	}
}
