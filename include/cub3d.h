#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define WIDTH 800
# define HEIGHT 600

struct t_data
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*ceiling;
	char	*floor;
	char	*map;
} typedef t_data;

void	init_hooks(void *mlx, void *win);
int		read_file(char *file, t_data *data);


#endif