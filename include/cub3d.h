/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:21:35 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/14 14:39:31 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*ceiling;
	char	*floor;
	char	**map;
	int		flag;
	int		img_width;
	int		img_height;
}	t_data;

void	init_hooks(void *mlx, void *win);
int		read_file(char *file, t_data *data);
int		check_walls(t_data *data);
int		check_map_closed(t_data *data);

// check_file.c
void	texture_parsing(char *line, t_data *data);
void	color_parsing(char *line, t_data *data);
void	store_map(char *line, t_data *data);
// check_map.c
int		check_top_wall(t_data *data);
int		check_bottom_wall(t_data *data);
int		check_left_and_right_walls(t_data *data);
// utils.c
int		check_map(t_data *data);
int		check_walls(t_data *data);
int		check_color_texture_not_null(t_data *data);
int		is_line_empty(char *line);
// utils2.c
int		is_cub(char *file);
char	*ft_trim(char *str);
// load.c
int		parse_color(char *line);
int		load_textures(t_data *data);

#endif