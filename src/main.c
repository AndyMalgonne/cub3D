/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:17:46 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/29 10:45:51 by amalgonn         ###   ########.fr       */
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

void cleanup(t_data *data)
{
    if (data->textures) {
        free(data->textures->no_path);
        free(data->textures->so_path);
        free(data->textures->ea_path);
        free(data->textures->we_path);
        if (data->mlx) {
            if (data->textures->no_img)
                mlx_destroy_image(data->mlx, data->textures->no_img);
            if (data->textures->so_img)
                mlx_destroy_image(data->mlx, data->textures->so_img);
            if (data->textures->ea_img)
                mlx_destroy_image(data->mlx, data->textures->ea_img);
            if (data->textures->we_img)
                mlx_destroy_image(data->mlx, data->textures->we_img);
        }
        free(data->textures);
    }
    free(data->ceiling);
    free(data->floor);
    free_map(data->map);
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    free(data->game);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	fill_ceiling_and_floor(t_data *data, int ceiling_color, int floor_color)
{
    int	x;
    int	y;

    y = 0;
    while (y < data->win_height / 2)
    {
        x = 0;
        while (x < data->win_width)
        {
            my_mlx_pixel_put(data->img_addr, data->img_line_len,
                data->img_bpp, x, y, ceiling_color);
            x++;
        }
        y++;
    }
    while (y < data->win_height)
    {
        x = 0;
        while (x < data->win_width)
        {
            my_mlx_pixel_put(data->img_addr, data->img_line_len,
                data->img_bpp, x, y, floor_color);
            x++;
        }
        y++;
    }
}

void	my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color)
{
	char	*dst;

	dst = addr + (y * line_length + x * (bpp / 8));
	*(unsigned int *)dst = color;
}

int main(int argc, char **argv)
{
    t_data data = {0};
    int color_ceiling, color_floor;

    if (argc != 2)
        return (printf("Error\nInvalid number of arguments\n"), 1);
    if (!init_struct(&data))
        return (printf("Error\ninit\n"), 1);
    if (!init_game(&data)) {
        cleanup(&data);
        return (printf("Error\ninit_game failed\n"), 1);
    }
    if (!parsing(argv[1], &data, &color_ceiling, &color_floor)) {
        cleanup(&data);
        return (1);
    }
    if (init_hooks(&data)) {
        cleanup(&data);
        return (printf("Error\ninit_hooks failed\n"), 1);
    }
    if (!load_textures(&data)) {
        cleanup(&data);
        return (printf("Error\nload_textures failed\n"), 1);
    }
    if (!get_player_position_and_direction(&data, data.game)) {
        cleanup(&data);
        return (0);
    }
    data.img = mlx_new_image(data.mlx, data.win_width, data.win_height);
    if (!data.img) {
        cleanup(&data);
        return (printf("Error\nmlx_new_image failed\n"), 1);
    }
    data.img_addr = mlx_get_data_addr(data.img, &data.img_bpp, &data.img_line_len, &data.img_endian);
    if (!data.img_addr) {
        cleanup(&data);
        return (printf("Error\nmlx_get_data_addr failed\n"), 1);
    }
    draw_scene(&data);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_loop(data.mlx);
    cleanup(&data);
    return (0);
}
