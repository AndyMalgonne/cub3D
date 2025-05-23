/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:21:35 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 04:30:09 by amalgonn         ###   ########.fr       */
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

# define MOVE_SPEED 0.5
# define ROT_SPEED 0.25

typedef struct s_game
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	oldtime;
}	t_game;

typedef struct s_texture
{
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	void	*no_img;
	void	*so_img;
	void	*ea_img;
	void	*we_img;
	char	*no_addr;
	char	*so_addr;
	char	*ea_addr;
	char	*we_addr;
	int		no_width;
	int		so_width;
	int		ea_width;
	int		we_width;
	int		no_height;
	int		so_height;
	int		ea_height;
	int		we_height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_data
{
	t_game		*game;
	void		*img;
	char		*img_addr;
	int			img_bpp;
	int			img_line_len;
	int			img_endian;
	t_texture	*textures;
	void		*mlx;
	void		*win;
	char		*ceiling;
	char		*floor;
	char		**map;
	int			flag;
	int			win_width;
	int			win_height;
}	t_data;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	double	perp_wall_dist;
	int		draw_start;
	int		draw_end;
	char	*texture;
	int		tex_width;
	int		tex_height;
	int		tex_x;
	int		line_height;
}	t_ray;

typedef struct s_texture_data
{
	char	*path;
	void	**img;
	char	**addr;
	int		*width;
	int		*height;
}	t_texture_data;

typedef struct s_draw_data
{
	int		x;
	int		y;
	double	tex_pos;
}	t_draw_data;

typedef struct s_move_data
{
	double	curr_x;
	double	curr_y;
	double	new_x;
	double	new_y;
	double	inter_x;
	double	inter_y;
}	t_move_data;

// parsing_utils.c
int		check_map(t_data *data);
int		check_walls(t_data *data);
int		check_color_texture_not_null(t_data *data);
int		is_line_empty(char *line);
// parsing_utils2.c
int		is_cub(char *file);
char	*ft_trim(char *str);
void	ft_error(char *msg);
void	free_map(char **map);
char	**reallocate_map(char **map, char *line);
// raycasting_utils.c
void	cleanup(t_data *data);
void	fill_ceiling_and_floor(t_data *data, int cc, int fc);
// raycasting_utils2.c
int		get_map_width(t_data *data, int row);
int		get_map_height(t_data *data);
int		is_valid_position(t_data *data, double x, double y);
void	calculate_intermediate_position(t_move_data *move, int step);
void	invalid_pos(t_move_data *move, double last_x, double last_y, int i);
// raycasting_utils3.c
int		mray(t_data *data, t_ray *ray, int map_height);
// check_file.c
int		texture_parsing(char *line, t_data *data);
int		color_parsing(char *line, t_data *data);
void	store_map(char *line, t_data *data);
// check_file2.c
int		read_file(char *file, t_data *data);
// check_map.c
int		check_top_wall(t_data *data);
int		check_bottom_wall(t_data *data);
int		check_left_and_right_walls(t_data *data);
// check_map2.c
int		check_map_closed(t_data *data);
// loop.c
int		init_hooks(t_data *data);
// load.c
int		parse_color(char *line);
int		load_textures(t_data *data);
// raycasting.c
void	init_ray(t_data *data, int x, t_ray *ray);
void	calc_delta_dist(t_ray *ray);
void	init_step(t_data *data, t_ray *ray);
void	cast_ray(t_data *data, t_ray *ray);
void	calc_perp_wall_dist(t_data *data, t_ray *ray);
// raycasting2.c
void	calc_draw_range(t_data *data, t_ray *ray);
void	select_texture(t_data *data, t_ray *ray);
void	calc_texture_x(t_data *data, t_ray *ray);
void	draw_vertical_line(t_data *data, int x, t_ray *ray);
// position.c
int		get_player_position_and_direction(t_data *data, t_game *game);
// rotate.c
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);
// movement.c
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	strafe_left(t_data *data);
void	strafe_right(t_data *data);
// main.c
void	draw_scene(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif