/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:56:22 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/28 11:39:40 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_iso(double *x, double *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.46373398);
	*y = -z + (prev_x + prev_y) * sin(0.46373398);
}

static void	_rotate_x(double *y, int *z, double ang)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(ang) + *z * sin(ang);
	*z = -prev_y * sin(ang) + *z * cos(ang);
}

static void	_rotate_y(double *x, int *z, double ang)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(ang) - *z * sin(ang);
	*z = prev_x * sin(ang) + *z * cos(ang);
}

static void	_rotate_z(double *x, double *y, double ang)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(ang) + prev_y * sin(ang);
	*y = -prev_x * sin(ang) + prev_y * cos(ang);
}

t_dot	proj(t_dot *a, t_fdf *data)
{
	t_dot	d;

	d = *a;
	d.x *= data->cam->zoom;
	d.y *= data->cam->zoom;
	d.x -= (data->map->m_width * data->cam->zoom) / 2;
	d.y -= (data->map->m_height * data->cam->zoom) / 2;
	_rotate_x(&d.y, &d.z, data->cam->ang_x);
	_rotate_y(&d.x, &d.z, data->cam->ang_y);
	_rotate_z(&d.x, &d.y, data->cam->ang_z);
	if (data->cam->var == 1)
		_iso(&d.x, &d.y, d.z);
	d.x += data->cam->align_x;
	d.y += data->cam->align_y;
	return (d);
}
