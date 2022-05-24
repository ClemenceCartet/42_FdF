/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:12:40 by ccartet           #+#    #+#             */
/*   Updated: 2022/01/31 12:18:18 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_color(char *str, t_coord *xyz)
{
	int	i;

	i = 2;
	if (ft_strncmp(str, "0x", 2) != 0)
		error("Incorrect color1");
	while (str[i] && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) || ft_check_sep(str[i], "abcdefABCDEF"))
			i++;
		else
			error("Incorrect color2");
	}
	if (i > 8)
		error("Incorrect color3");
	xyz->color = ft_atoi_base_16(&str[2]);
}

void	check_map_error(char *str, t_coord *xyz)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != ',')
			error("Incorrect data in file");
		if (str[i] == ',')
		{
			check_color(&str[i + 1], xyz);
			return ;
		}
		i++;
	}
}

t_coord	write_coord(char *str, int x, int y)
{
	t_coord	xyz;

	xyz.x = x;
	xyz.y = y;
	xyz.z = ft_atoi(str);
	xyz.color = 0xfffafa;
	check_map_error(str, &xyz);
	return (xyz);
}

void	get_line(char *str, t_coord **tab, int y, t_vars *fdf)
{
	char	**spl_line;
	int		x;

	x = 0;
	tab[y] = malloc(sizeof(t_coord) * fdf->nbcol * fdf->nblin);
	if (!tab[y])
		error("Malloc problem");
	spl_line = ft_split(str, ' ');
	while (spl_line[x] && ft_strncmp(spl_line[x], "\n", 1) != 0)
	{
		tab[y][x] = write_coord(spl_line[x], x, y);
		free(spl_line[x]);
		x++;
	}
	free(spl_line);
}

void	get_map(char *str, t_vars *fdf)
{
	char	*line;
	int		fd;
	int		y;

	y = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		error("fd problem");
	fdf->tab = malloc(sizeof(t_coord *) * fdf->nblin);
	if (!fdf->tab)
		error("Malloc problem");
	line = get_next_line(fd);
	while (line)
	{
		get_line(line, fdf->tab, y, fdf);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	if (close(fd) == -1)
		error("fd problem");
}
