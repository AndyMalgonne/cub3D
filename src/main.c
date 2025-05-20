/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:17:46 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 05:45:39 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_struct(t_data *data)
{
	data->textures = ft_calloc(1, sizeof(t_texture));
	if (!data->textures)
	{
		printf("Error\nFailed to allocate memory for textures\n");
		return (0);
	}
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

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		ft_error("Failed to allocate memory for game");
		return (0);
	}
	data->game = game;
	*data->game = (t_game){0};
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

int	main(int argc, char **argv)
{
	t_data	data;
	int		color_ceiling;
	int		color_floor;

	data = (t_data){0};
	if (argc != 2)
		return (printf("Error\nInvalid number of arguments\n"), 1);
	if (!init_struct(&data) || !init_game(&data)
		|| !parsing(argv[1], &data, &color_ceiling, &color_floor)
		|| !load_textures(&data) || init_hooks(&data)
		|| !get_player_position_and_direction(&data, data.game))
		return (cleanup(&data), 1);
	data.img = mlx_new_image(data.mlx, data.win_width, data.win_height);
	if (!data.img)
		return (printf("Error\nImage initialization failed\n"),
			cleanup(&data), 1);
	data.img_addr = mlx_get_data_addr(data.img, &data.img_bpp,
			&data.img_line_len, &data.img_endian);
	if (!data.img_addr)
		return (printf("Error\nmlx_get_data_addr failed\n"), cleanup(&data), 1);
	return (draw_scene(&data),
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0),
		mlx_loop(data.mlx), cleanup(&data), 0);
}
