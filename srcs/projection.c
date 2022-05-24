/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:24:22 by ccartet           #+#    #+#             */
/*   Updated: 2022/02/09 11:41:34 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_coord *xyz, t_vars *fdf)
{
	double	prev_y;

	prev_y = (double)xyz->y;
	xyz->y = prev_y * cos(fdf->cam->rad_x) + xyz->z * sin(fdf->cam->rad_x);
	xyz->z = -prev_y * sin(fdf->cam->rad_x) + xyz->z * cos(fdf->cam->rad_x);
}

void	rotate_y(t_coord *xyz, t_vars *fdf)
{
	double	prev_x;

	prev_x = (double)xyz->x;
	xyz->x = prev_x * cos(fdf->cam->rad_y) + xyz->z * sin(fdf->cam->rad_y);
	xyz->z = -prev_x * sin(fdf->cam->rad_y) + xyz->z * cos(fdf->cam->rad_y);
}

void	rotate_z(t_coord *xyz, t_vars *fdf)
{
	double	prev_x;
	double	prev_y;

	prev_x = (double)xyz->x;
	prev_y = (double)xyz->y;
	xyz->x = prev_x * cos(fdf->cam->rad_z) - prev_y * sin(fdf->cam->rad_z);
	xyz->y = prev_x * sin(fdf->cam->rad_z) + prev_y * cos(fdf->cam->rad_z);
}

void	zoom(t_coord *tmp, t_coord *xyz, t_vars *fdf)
{
	tmp->x = (fdf->wdw_width * ((xyz->x - fdf->nbcol / 2)
				/ (fdf->nbcol * (2 * M_SQRT2)))) * fdf->cam->zoom;
	tmp->y = (fdf->wdw_height * ((xyz->y - fdf->nblin / 2)
				/ (fdf->nblin * (2 * M_SQRT2)))) * fdf->cam->zoom;
	tmp->z = xyz->z * (fdf->cam->zoom + fdf->cam->z_height);
}

t_coord	*project(t_coord *xyz, t_vars *fdf)
{
	t_coord	*tmp;
	double	prev_x;
	double	prev_y;

	tmp = malloc(sizeof(t_coord));
	if (!tmp)
	{
		mlx_destroy_window(fdf->ptr, fdf->wdw);
		feel_free(fdf);
		error("Malloc problem");
	}
	zoom(tmp, xyz, fdf);
	tmp->color = xyz->color;
	rotate_x(tmp, fdf);
	rotate_y(tmp, fdf);
	rotate_z(tmp, fdf);
	prev_x = tmp->x;
	prev_y = tmp->y;
	tmp->x = (prev_x - prev_y) * cos(0.523599)
		+ fdf->cam->move_lr * 2 + fdf->wdw_width / 2;
	tmp->y = -tmp->z + (prev_x + prev_y) * sin(0.523599)
		+ fdf->cam->move_ud * 2 + fdf->wdw_height / 2;
	return (tmp);
}
