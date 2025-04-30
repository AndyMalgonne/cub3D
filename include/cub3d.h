/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:21:35 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/30 07:59:57 by amalgonn         ###   ########.fr       */
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

typedef struct s_game
{
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    double time;
    double oldtime;
} t_game;

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
} t_texture;

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
} t_data;

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
} t_ray;

typedef struct s_texture_data
{
    char	*path;
    void	**img;
    char	**addr;
    int		*width;
    int		*height;
}	t_texture_data;

int		init_hooks(t_data *data);
int		read_file(char *file, t_data *data);
int		check_walls(t_data *data);
int		check_map_closed(t_data *data);

// check_file.c
int	texture_parsing(char *line, t_data *data);
int	color_parsing(char *line, t_data *data);
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
void	ft_error(char *msg);
void	free_map(char **map);
char	**reallocate_map(char **map, char *line);
// load.c
int		parse_color(char *line);
int		load_textures(t_data *data);
// raytracing.c
void	init_ray(t_data *data, int x, t_ray *ray);
void	calc_delta_dist(t_ray *ray);
void	init_step(t_data *data, t_ray *ray);
void	cast_ray(t_data *data, t_ray *ray);
void	calc_perp_wall_dist(t_data *data, t_ray *ray);
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
void draw_scene(t_data *data);
void my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color);
void fill_ceiling_and_floor(t_data *data, int ceiling_color, int floor_color);
void cleanup(t_data *data);

#endif