/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 07:40:07 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/28 11:30:52 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	_hdigit( char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (c - '0');
}

static int	_hex_to_dec(char *hx)
{
	int		s;
	int		p;
	char	*cpi;

	cpi = hx;
	p = 0;
	s = 0;
	while (*cpi && *cpi != '\n')
		cpi++;
	while (hx != cpi--)
	{
		s += _hdigit(*cpi) << p;
		p += 4;
	}
	return (s);
}

void	u_fill_clr(t_fdf *data, char *line)
{
	static int	i = 0;
	int			j;
	char		**nums;
	char		*s1;

	nums = ft_split(line, ' ');
	j = 0;
	while (nums[j])
	{
		s1 = ft_strchr(nums[j], ',');
		if (s1)
			data->dot[i].color = _hex_to_dec(s1 + 3);
		free(nums[j++]);
		i++;
	}
	s1 = NULL;
	free(nums);
}

void	_fill_mtx(int *line_z, char *line)
{
	int		i;
	char	**nums;

	nums = ft_split(line, ' ');
	i = 0;
	while (nums[i])
	{
		line_z[i] = ft_atoi(nums[i]);
		free(nums[i++]);
	}
	free(nums);
}

void	fill_dot(t_fdf *data, t_dot	*new_dot)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = 0;
	while (y < data->map->m_height)
	{
		x = 0;
		while (x < data->map->m_width)
		{
			new_dot[i].x = x;
			new_dot[i].y = y;
			new_dot[i].z = data->map->m_z[y][x++];
			if (mod(new_dot[i].z))
				new_dot[i++].color = RED;
			else
				new_dot[i++].color = WHITE;
		}
		y++;
	}
}
