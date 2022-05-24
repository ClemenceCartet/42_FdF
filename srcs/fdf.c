/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:10:21 by ccartet           #+#    #+#             */
/*   Updated: 2022/02/09 11:01:03 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_coord *p1, t_coord *p2, t_vars *fdf)
{
	fdf->x = p1->x;
	fdf->y = p1->y;
	fdf->dx = abs(p2->x - p1->x);
	fdf->dy = abs(p2->y - p1->y);
	draw_line_utils(p1, p2, fdf);
	while (fdf->x != p2->x || fdf->y != p2->y)
	{
		ft_put_pixel(fdf->x, fdf->y, get_color(p1, p2, fdf), fdf);
		fdf->e2 = fdf->err;
		if (fdf->e2 > -(fdf->dx))
		{
			fdf->err -= fdf->dy;
			fdf->x += fdf->sign_x;
		}
		if (fdf->e2 < fdf->dy)
		{
			fdf->err += fdf->dx;
			fdf->y += fdf->sign_y;
		}
	}
}

void	draw_map(t_vars *fdf, t_coord **map)
{
	t_coord	*p1;
	t_coord	*p2;
	t_coord	*p3;

	fdf->nb_y = -1;
	while (++fdf->nb_y < fdf->nblin)
	{
		fdf->nb_x = -1;
		while (++fdf->nb_x < fdf->nbcol)
		{
			p1 = project(&map[fdf->nb_y][fdf->nb_x], fdf);
			p2 = project(&map[fdf->nb_y][fdf->nb_x + 1], fdf);
			if (fdf->nb_x < fdf->nbcol - 1)
				draw_line(p1, p2, fdf);
			if (fdf->nb_y < fdf->nblin - 1)
			{
				p3 = project(&map[fdf->nb_y + 1][fdf->nb_x], fdf);
				draw_line(p1, p3, fdf);
				free(p3);
			}
			free(p1);
			free(p2);
		}
	}
}

void	display_commands(t_vars *fdf)
{
	mlx_string_put(fdf->ptr, fdf->wdw, 1680, 30, 0xfffafa, "Commandes");
	mlx_string_put(fdf->ptr, fdf->wdw, 1680, 60, 0xffdab9, "Zoom : +/-");
	mlx_string_put(fdf->ptr, fdf->wdw, 1680, 75, 0xffdab9, "Move : Fleches");
	mlx_string_put(fdf->ptr, fdf->wdw, 1680, 90, 0xffdab9, "Rotations :");
	mlx_string_put(fdf->ptr, fdf->wdw, 1700, 105, 0xffdab9, "Axe X : 4/5");
	mlx_string_put(fdf->ptr, fdf->wdw, 1700, 120, 0xffdab9, "Axe Y : 1/2");
	mlx_string_put(fdf->ptr, fdf->wdw, 1700, 135, 0xffdab9, "Axe Z : 7/8");
	mlx_string_put(fdf->ptr, fdf->wdw, 1680, 150, 0xffdab9, "Amplitude : 3/6");
}

void	display_map(t_vars *fdf)
{
	fdf->img.img = mlx_new_image(fdf->ptr, fdf->wdw_width,
			fdf->wdw_height);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &(fdf->img.bpp),
			&(fdf->img.line_length), &(fdf->img.endian));
	draw_map(fdf, fdf->tab);
	if (fdf->mouse2->x != 0 && fdf->mouse2->y != 0)
		draw_line(fdf->mouse1, fdf->mouse2, fdf);
	mlx_put_image_to_window(fdf->ptr, fdf->wdw, fdf->img.img, 0, 0);
	mlx_destroy_image(fdf->ptr, fdf->img.img);
	display_commands(fdf);
}

int	main(int argc, char **argv)
{
	t_vars	*fdf;

	if (argc != 2)
		error("Just one argument !");
	if (!ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
		error("Incorrect input file format");
	fdf = malloc(sizeof(t_vars));
	if (!fdf)
		error("Malloc problem");
	ft_init(fdf);
	get_size(argv[1], fdf);
	get_map(argv[1], fdf);
	fdf->ptr = mlx_init();
	fdf->wdw = mlx_new_window(fdf->ptr, fdf->wdw_width,
			fdf->wdw_height, "FDF");
	display_map(fdf);
	mlx_hook(fdf->wdw, 4, 1L << 2, mouse_hook, fdf);
	mlx_hook(fdf->wdw, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->wdw, 17, 1L << 17, exit_x, fdf);
	mlx_loop(fdf->ptr);
	return (0);
}
