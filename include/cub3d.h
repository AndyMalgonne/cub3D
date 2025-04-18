/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:21:35 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/18 14:56:10 by amalgonn         ###   ########.fr       */
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
# include <math.h>

#define MOVE_SPEED 0.05
#define ROT_SPEED 0.05
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldtime;
}	t_game;

typedef struct s_data
{
	t_game	*game;
	t_img	img;
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
	int		win_width;
	int		win_height;
}	t_data;

int		init_hooks(t_data *data);
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
// raycasting.c
int		get_player_position_and_direction(t_data *data, t_game *game);
// rotate.c
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);
// movement.c
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	strafe_left(t_data *data);
void	strafe_right(t_data *data);

#endif