/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:09:21 by ccartet           #+#    #+#             */
/*   Updated: 2022/02/11 11:13:27 by ccartet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_index_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base_16(char *str)
{
	int		num;
	int		i;
	int		res;
	char	*base_min;
	char	*base_maj;

	base_min = "0123456789abcdef";
	base_maj = "0123456789ABCDEF";
	num = 1;
	i = 0;
	res = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			res = res * ft_strlen(base_maj) + ft_index_base(str[i], base_maj);
		else if (str[i] >= 'a' && str[i] <= 'f')
			res = res * ft_strlen(base_min) + ft_index_base(str[i], base_min);
		else
			res = res * ft_strlen(base_maj) + ft_index_base(str[i], base_maj);
		i++;
	}
	return (res * num);
}

int	ft_check_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_col(char const *s, char sep)
{
	int	i;
	int	mot;

	i = 0;
	mot = 0;
	while (s[i] != '\n')
	{
		if ((i == 0) && s[0] != sep)
			mot++;
		else if (s[i] != sep && s[i - 1] == sep)
			mot++;
		i++;
	}
	return (mot);
}

void	get_size(char *str, t_vars *fdf)
{
	char	*line;
	int		fd;
	int		size_tab;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		error("fd problem");
	line = get_next_line(fd);
	if (!line)
		error("Empty file !");
	size_tab = ft_count_col(line, ' ');
	fdf->nbcol = size_tab;
	while (line)
	{
		// if (ft_count_col(line, ' ') != size_tab)
		// 	error("Map is not rectangular !");
		free(line);
		line = get_next_line(fd);
		fdf->nblin++;
	}
	if (close(fd) == -1)
		error("fd problem");
}
