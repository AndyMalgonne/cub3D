/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:17:46 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/29 08:41:34 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_struct(t_data *data)
{
	data->textures = malloc(sizeof(t_texture));
	if (!data->textures)
	{
		printf("Error\nFailed to allocate memory for textures\n");
		return (0);
	}
	data->textures->no_path = NULL;
	data->textures->so_path = NULL;
	data->textures->ea_path = NULL;
	data->textures->we_path = NULL;
	data->textures->no_img = NULL;
	data->textures->so_img = NULL;
	data->textures->ea_img = NULL;
	data->textures->we_img = NULL;
	data->textures->no_addr = NULL;
	data->textures->so_addr = NULL;
	data->textures->ea_addr = NULL;
	data->textures->we_addr = NULL;
	data->textures->no_width = 0;
	data->textures->so_width = 0;
	data->textures->ea_width = 0;
	data->textures->we_width = 0;
	data->textures->no_height = 0;
	data->textures->so_height = 0;
	data->textures->ea_height = 0;
	data->textures->we_height = 0;
	data->textures->bpp = 0;
	data->textures->line_len = 0;
	data->textures->endian = 0;
	data->game = NULL;
	data->img = NULL;
	data->img_addr = NULL;
	data->img_bpp = 0;
	data->img_line_len = 0;
	data->img_endian = 0;
	data->ceiling = NULL;
	data->floor = NULL;
	data->map = NULL;
	data->flag = 0;
	data->win = NULL;
	data->win_height = 0;
	data->win_width = 0;
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error\nmlx_init failed\n");
		free(data->textures);
		return (0);
	}
	return (1);
}

int	init_game(t_data *data)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		ft_error("Failed to allocate memory for game");
		return (0);
	}
	data->game = game;
	data->game->pos_x = 0;
	data->game->pos_y = 0;
	data->game->dir_x = 0;
	data->game->dir_y = 0;
	data->game->plane_x = 0;
	data->game->plane_y = 0;
	data->game->time = 0;
	data->game->oldtime = 0;
	return (1);
}

int	parsing(char *file, t_data *data, int *color_ceiling, int *color_floor)
{
	if (!read_file(file, data))
		return (0);
	if (!check_map(data))
		return (0);
	if (!check_color_texture_not_null(data))
		return (0);
	*color_ceiling = parse_color(data->ceiling);
	if (*color_ceiling == -1)
		return (0);
	*color_floor = parse_color(data->floor);
	if (*color_floor == -1)
		return (0);
	return (1);
}

void	my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color)
{
	char	*dst;

	dst = addr + (y * line_length + x * (bpp / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		color_ceiling;
	int		color_floor;

	if (argc != 2)
		return (printf("Error\nInvalid number of arguments\n"), 1);
	if (!init_struct(&data))
		return (printf("Error\ninit\n"), 1);
	if (!init_game(&data))
		return (printf("Error\ninit_game failed\n"), 1);
	if (!parsing(argv[1], &data, &color_ceiling, &color_floor))
		return (1);
	if (init_hooks(&data))
		return (printf("Error\ninit_hooks failed\n"), 1);
	if (!load_textures(&data))
		return (printf("Error\nload_textures failed\n"), 1);
	if (!get_player_position_and_direction(&data, data.game))
		return (0);
	data.img = mlx_new_image(data.mlx, data.win_width, data.win_height);
	if (!data.img)
	{
		printf("Error\nmlx_new_image failed\n");
		return (1);
	}
	data.img_addr = mlx_get_data_addr(data.img, &data.img_bpp, &data.img_line_len, &data.img_endian);
	if (!data.img_addr)
	{
		printf("Error\nmlx_get_data_addr failed\n");
		return (1);
	}
	draw_scene(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	if (data.textures->no_path)
		free(data.textures->no_path);
	if (data.textures->so_path)
		free(data.textures->so_path);
	if (data.textures->ea_path)
		free(data.textures->ea_path);
	if (data.textures->we_path)
		free(data.textures->we_path);
	if (data.textures->no_img)
		mlx_destroy_image(data.mlx, data.textures->no_img);
	if (data.textures->so_img)
		mlx_destroy_image(data.mlx, data.textures->so_img);
	if (data.textures->ea_img)
		mlx_destroy_image(data.mlx, data.textures->ea_img);
	if (data.textures->we_img)
		mlx_destroy_image(data.mlx, data.textures->we_img);
	if (data.ceiling)
		free(data.ceiling);
	if (data.floor)
		free(data.floor);
	if (data.img)
		mlx_destroy_image(data.mlx, data.img);
	if (data.textures)
		free(data.textures);
	return (0);
}
