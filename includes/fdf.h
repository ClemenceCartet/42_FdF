/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:10:38 by ccartet           #+#    #+#             */
/*   Updated: 2022/01/31 12:21:17 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <string.h>

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_coord;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_camera
{
	int			zoom;
	int			move_ud;
	int			move_lr;
	double		rad_x;
	double		rad_y;
	double		rad_z;
	int			z_height;
}				t_camera;

typedef struct s_vars
{
	void		*ptr;
	void		*wdw;
	int			wdw_width;
	int			wdw_height;
	int			nbcol;
	int			nblin;
	int			dx;
	int			dy;
	int			sign_x;
	int			sign_y;
	int			err;
	int			e2;
	int			nb_x;
	int			nb_y;
	int			i;
	int			x;
	int			y;
	t_coord		*mouse1;
	t_coord		*mouse2;
	t_data		img;
	t_camera	*cam;
	t_coord		**tab;
}				t_vars;

void		display_map(t_vars *fdf);
void		display_commands(t_vars *fdf);
void		draw_map(t_vars *fdf, t_coord **map);
void		error(char *str);
void		get_size(char *str, t_vars *fdf);
void		get_map(char *str, t_vars *fdf);
void		get_line(char *str, t_coord **tab, int y, t_vars *fdf);
void		check_map_error(char *str, t_coord *xyz);
void		check_color(char *str, t_coord *xyz);
t_coord		write_coord(char *str, int x, int y);
int			ft_count_col(char const *s, char sep);
int			ft_check_sep(char c, char *sep);
int			ft_atoi_base_16(char *str);
int			ft_index_base(char c, char *base);
void		feel_free(t_vars *fdf);
void		ft_init(t_vars *fdf);
t_coord		*ft_init_xyz(void);
t_camera	*ft_init_camera(void);
int			exit_x(t_vars *fdf);
int			key_hook(int keycode, t_vars *fdf);
void		key_rotate(int keycode, t_vars *fdf);
int			mouse_hook(int button, int x, int y, t_vars *fdf);
void		draw_line(t_coord *p1, t_coord *p2, t_vars *fdf);
void		draw_line_utils(t_coord *p1, t_coord *p2, t_vars *fdf);
void		ft_put_pixel(int x, int y, int color, t_vars *fdf);
double		percent(int start, int end, int current);
int			get_light(int start, int end, double percentage);
int			get_color(t_coord *start, t_coord *end, t_vars *fdf);
t_coord		*project(t_coord *xyz, t_vars *fdf);
void		zoom(t_coord *tmp, t_coord *xyz, t_vars *fdf);
void		rotate_x(t_coord *xyz, t_vars *fdf);
void		rotate_y(t_coord *xyz, t_vars *fdf);
void		rotate_z(t_coord *xyz, t_vars *fdf);

#endif
