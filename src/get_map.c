/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:29:48 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/28 11:16:15 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_get_wight(t_map *map, char *str)
{
	int		fd;
	char	*temp_line;

	fd = open(str, O_RDONLY, 0);
	temp_line = get_next_line(fd);
	map->m_width = count_words(temp_line, ' ');
	free(temp_line);
	close(fd);
}

static void	_get_height(t_map *map, char *str)
{
	int		fd;
	int		h;
	char	*temp_line;

	h = 0;
	fd = open(str, O_RDONLY, 0);
	temp_line = get_next_line(fd);
	while (temp_line && ++h)
	{
		free(temp_line);
		temp_line = get_next_line(fd);
	}
	map->m_height = h;
	free(temp_line);
	close(fd);
}

static void	_fill_clr(t_fdf *data, char *str)
{
	int		fd;
	char	*temp_line;

	fd = open(str, O_RDONLY, 0);
	temp_line = get_next_line(fd);
	while (temp_line)
	{
		u_fill_clr(data, temp_line);
		free(temp_line);
		temp_line = get_next_line(fd);
	}
	free(temp_line);
	close(fd);
}

static void	_get_m_z(t_map *map, char *str)
{
	int		i;
	int		fd;
	char	*temp_line;

	i = 0;
	map->m_z = (int **)malloc(sizeof(int *) * (map->m_height + 1));
	while (i < map->m_height)
		map->m_z[i++] = (int *)malloc(sizeof(int) * (map->m_width + 1));
	fd = open(str, O_RDONLY, 0);
	i = 0;
	temp_line = get_next_line(fd);
	while (temp_line)
	{
		_fill_mtx(map->m_z[i++], temp_line);
		free(temp_line);
		temp_line = get_next_line(fd);
	}
	map->m_z[i] = NULL;
	free(temp_line);
	close(fd);
}

void	read_file(t_fdf *data, char *str)
{
	check_file(data, str);
	data->map = map_init(data);
	_get_wight(data->map, str);
	_get_height(data->map, str);
	_get_m_z(data->map, str);
	data->map->m_size = data->map->m_height * data->map->m_width;
	data->dot = dot_init(data);
	_fill_clr(data, str);
}
