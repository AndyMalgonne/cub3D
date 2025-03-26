/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:17:46 by amalgonn          #+#    #+#             */
/*   Updated: 2025/03/26 11:55:42 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	is_cub(char *file)
{
	int i;

	i = ft_strlen(file);
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || file[i - 4] != '.')
		printf("Error\nInvalid file extension\n");
}

// int main(int argc, char **argv)
// {
// 	if (argc =! 2)
// 		ft_error("Error\nInvalid number of arguments\n");
// 	if(!is_cube(argv[1]))
// 		ft_error("Error\nInvalid file extension\n");
// 	return (0);
// }



int main()
{
    void *mlx;
    void *win;
    void *img;
    int img_width, img_height;
    mlx = mlx_init();
    if (!mlx)
    {
        printf("Erreur : Impossible d'initialiser MLX\n");
        return (1);
    }
    win = mlx_new_window(mlx, 800, 600, "Test MLX");
    if (!win)
    {
        printf("Erreur : Impossible de créer la fenêtre\n");
        return (1);
    }
    img = mlx_xpm_file_to_image(mlx, "./texture/wall.xpm", &img_width, &img_height);
    if (!img)
    {
        printf("Erreur : Impossible de charger l'image\n");
        return (1);
    }
    mlx_put_image_to_window(mlx, win, img, 0, 0);
	init_hooks(mlx, win);
    mlx_loop(mlx);
    return (0);
}