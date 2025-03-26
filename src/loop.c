/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:48:40 by amalgonn          #+#    #+#             */
/*   Updated: 2025/03/26 11:53:48 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int handle_keypress(int keycode, void *param)
{
	(void)param;
    if (keycode == XK_Escape)
    {
        printf("ESC pressed. Exiting...\n");
        exit(0);
    }
    return (0);
}

int handle_close(void *param)
{
	(void)param;
    printf("Window closed. Exiting...\n");
    exit(0);
    return (0);
}

void	init_hooks(void *mlx, void *win)
{
	(void)mlx;
	mlx_hook(win, KeyPress, KeyPressMask, handle_keypress, NULL);
	mlx_hook(win, DestroyNotify, StructureNotifyMask, handle_close, NULL);
}
