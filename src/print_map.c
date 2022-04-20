/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 05:19:29 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/28 11:38:10 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_set_background(t_mlx *fdf)
{
	int	*img;
	int	i;

	i = 0;
	img = (int *)(fdf->p_addr);
	while (i < HEIGHT * WIDTH)
		img[i++] = BACKGROUND >> 2;
}

static int	_put_pixel(t_dot *a, int color, t_mlx *mlx)
{
	char	*dst;

	if ((a->x < WIDTH && a->y < HEIGHT) && (a->x > 0 && a->y > 0))
	{
		dst = mlx->p_addr + (((int)a->y * mlx->len)
				+ ((int)a->x * (mlx->bpp / 8)));
		*(unsigned int *)dst = color;
	}
	return (1);
}

static int	_get_color(t_dot start, t_dot end)
{
	if (start.color > end.color)
		return (start.color);
	else if (start.color < end.color)
		return (end.color);
	return (end.color);
}

static void	_dda_line(t_dot a, t_dot b, t_fdf *data)
{
	t_dot	delta;
	t_dot	cur;
	double	step;

	delta.x = (b.x - a.x);
	delta.y = (b.y - a.y);
	step = find_max(mod(delta.x), mod(delta.y));
	delta.x /= step;
	delta.y /= step;
	cur = a;
	while ((int)step-- && _put_pixel(&cur, _get_color(cur, b), data->mlx))
	{
		cur.x += delta.x;
		cur.y += delta.y;
	}
}

void	draw(t_fdf *data)
{
	int	i;

	_set_background(data->mlx);
	i = -1;
	while (++i < data->map->m_size)
	{
		if ((i + 1) % data->map->m_width != 0)
			_dda_line(proj(&data->dot[i], data),
				proj(&data->dot[i + 1], data), data);
		if (i / data->map->m_width != data->map->m_height - 1)
			_dda_line(proj(&data->dot[i], data),
				proj(&data->dot[i + data->map->m_width], data), data);
	}
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win,
		data->mlx->p_img, 0, 0);
}
