/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:33:14 by ccartet           #+#    #+#             */
/*   Updated: 2022/02/09 11:39:18 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(char *str)
{
	ft_printf("%s", str);
	exit(0);
}

int	exit_x(t_vars *fdf)
{
	mlx_destroy_window(fdf->ptr, fdf->wdw);
	feel_free(fdf);
	exit(0);
	return (0);
}

void	key_rotate(int keycode, t_vars *fdf)
{
	if (keycode == 86)
		fdf->cam->rad_x -= 0.05;
	else if (keycode == 87)
		fdf->cam->rad_x += 0.05;
	else if (keycode == 84)
		fdf->cam->rad_y -= 0.05;
	else if (keycode == 83)
		fdf->cam->rad_y += 0.05;
	else if (keycode == 91)
		fdf->cam->rad_z -= 0.05;
	else if (keycode == 89)
		fdf->cam->rad_z += 0.05;
}

int	key_hook(int keycode, t_vars *fdf)
{
	if (keycode == 69)
		fdf->cam->zoom += 1;
	else if (keycode == 78)
		fdf->cam->zoom -= 1;
	else if (keycode == 126)
		fdf->cam->move_ud += 10;
	else if (keycode == 125)
		fdf->cam->move_ud -= 10;
	else if (keycode == 124)
		fdf->cam->move_lr -= 10;
	else if (keycode == 123)
		fdf->cam->move_lr += 10;
	else if (keycode == 88)
		fdf->cam->z_height += 1;
	else if (keycode == 85)
		fdf->cam->z_height -= 1;
	key_rotate(keycode, fdf);
	display_map(fdf);
	if (keycode == 53)
		exit_x(fdf);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *fdf)
{
	if (button == 4)
		fdf->cam->zoom += 1;
	else if (button == 5)
		fdf->cam->zoom -= 1;
	if (button == 1)
	{
		free(fdf->mouse1);
		fdf->mouse1 = ft_init_xyz();
		fdf->mouse1->x = x;
		fdf->mouse1->y = y;
		fdf->mouse1->color = 0xffd700;
	}
	if (button == 2)
	{
		free(fdf->mouse2);
		fdf->mouse2 = ft_init_xyz();
		fdf->mouse2->x = x;
		fdf->mouse2->y = y;
		fdf->mouse2->color = 0xf0f8ff;
	}
	display_map(fdf);
	return (0);
}
