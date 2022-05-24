/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:44:46 by ccartet           #+#    #+#             */
/*   Updated: 2022/01/31 12:18:54 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	feel_free(t_vars *fdf)
{
	int	y;

	y = 0;
	free(fdf->cam);
	free(fdf->mouse1);
	free(fdf->mouse2);
	while (y < fdf->nblin)
	{
		free(fdf->tab[y]);
		y++;
	}
	free(fdf->tab);
	free(fdf);
}

t_coord	*ft_init_xyz(void)
{
	t_coord	*xyz;

	xyz = malloc(sizeof(t_coord));
	if (!xyz)
		error("Malloc problem");
	xyz->x = 0;
	xyz->y = 0;
	xyz->z = 0;
	xyz->color = 0xfffafa;
	return (xyz);
}

t_camera	*ft_init_camera(void)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	if (!cam)
		error("Malloc problem");
	cam->zoom = 1;
	cam->move_ud = 0;
	cam->move_lr = 0;
	cam->rad_x = 0;
	cam->rad_y = 0;
	cam->rad_z = 0;
	cam->z_height = 1;
	return (cam);
}

void	ft_init(t_vars *fdf)
{
	fdf->ptr = NULL;
	fdf->wdw = NULL;
	fdf->wdw_width = 1920;
	fdf->wdw_height = 1080;
	fdf->nbcol = 0;
	fdf->nblin = 0;
	fdf->dx = 0;
	fdf->dy = 0;
	fdf->sign_x = 0;
	fdf->sign_y = 0;
	fdf->err = 0;
	fdf->e2 = 0;
	fdf->nb_x = -1;
	fdf->nb_y = -1;
	fdf->i = -1;
	fdf->x = 0;
	fdf->y = 0;
	fdf->cam = ft_init_camera();
	fdf->mouse1 = ft_init_xyz();
	fdf->mouse2 = ft_init_xyz();
}
