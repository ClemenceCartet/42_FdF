/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:28:52 by ccartet           #+#    #+#             */
/*   Updated: 2022/01/25 14:45:25 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1);
	return (placement / distance);
}

int	get_light(int start, int end, double percentage)
{
	double	result;

	result = (1 - percentage) * start + percentage * end;
	return ((int)result);
}

int	get_color(t_coord *start, t_coord *end, t_vars *fdf)
{
	int		r;
	int		g;
	int		b;
	double	pcg;

	if (start->color == end->color)
		return (start->color);
	if (fdf->dx > fdf->dy)
		pcg = percent(start->x, end->x, fdf->x);
	else
		pcg = percent(start->y, end->y, fdf->y);
	r = get_light((start->color >> 16) & 0xFF, (end->color >> 16) & 0xFF, pcg);
	g = get_light((start->color >> 8) & 0xFF, (end->color >> 8) & 0xFF, pcg);
	b = get_light(start->color & 0xFF, end->color & 0xFF, pcg);
	return ((r << 16) | (g << 8) | b);
}

void	draw_line_utils(t_coord *p1, t_coord *p2, t_vars *fdf)
{
	if (p1->x < p2->x)
		fdf->sign_x = 1;
	else
		fdf->sign_x = -1;
	if (p1->y < p2->y)
		fdf->sign_y = 1;
	else
		fdf->sign_y = -1;
	if (fdf->dx > fdf->dy)
		fdf->err = fdf->dx / 2;
	else
		fdf->err = -(fdf->dy) / 2;
}

void	ft_put_pixel(int x, int y, int color, t_vars *fdf)
{
	int	i;

	if (x > 0 && x < fdf->wdw_width && y > 0 && y < fdf->wdw_height)
	{
		i = (y * fdf->img.line_length) + (x * (fdf->img.bpp / 8));
		fdf->img.addr[i] = 0;
		fdf->img.addr[i++] = color;
		fdf->img.addr[i++] = (color >> 8);
		fdf->img.addr[i++] = (color >> 16);
	}
}
