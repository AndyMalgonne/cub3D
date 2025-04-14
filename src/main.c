/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:17:46 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/14 14:49:02 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->ceiling = NULL;
	data->floor = NULL;
	data->map = NULL;
	data->flag = 0;
	data->mlx = 0;
	data->img_height = 0;
	data->img_width = 0;
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
	if (!load_textures(data))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		color_ceiling;
	int		color_floor;

	init_struct(&data);
	if (argc != 2)
		return (printf("Error\nInvalid number of arguments\n"), 1);
	if (!parsing(argv[1], &data, &color_ceiling, &color_floor))
		return (1);
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		printf("Error\nmlx_init failed\n");
		return (1);
	}
	data.win = mlx_new_window(data.mlx, 500, 500, "cub3D Textures Test");
	if (!data.win)
	{
		printf("Error\nmlx_new_window failed\n");
		return (1);
	}
	mlx_loop(data.mlx);
	if (data.no)
		free(data.no);
	if (data.so)
		free(data.so);
	if (data.ea)
		free(data.ea);
	if (data.we)
		free(data.we);
	if (data.ceiling)
		free(data.ceiling);
	if (data.floor)
		free(data.floor);
	if (data.map)
		free(data.map);
	return (0);
}
