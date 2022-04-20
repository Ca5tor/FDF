/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:09:41 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/28 13:33:03 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_xyz(int key, t_fdf *data)
{
	static double	xyz = 0.1f;

	if (key == K_Q)
		data->cam->ang_x -= xyz;
	else if (key == K_A)
		data->cam->ang_x += xyz;
	else if (key == K_W)
		data->cam->ang_y -= xyz;
	else if (key == K_S)
		data->cam->ang_y += xyz;
	else if (key == K_E)
		data->cam->ang_z -= xyz;
	else if (key == K_D)
		data->cam->ang_z += xyz;
}

void	change_proj(int key, t_fdf *data)
{
	data->cam->ang_x = 0;
	data->cam->ang_y = 0;
	data->cam->ang_z = 0;
	if (key == K_Z)
		data->cam->var = 0;
	else if (key == K_X)
	{
		data->cam->ang_x = -1.570796;
		data->cam->var = 0;
	}
	else if (key == K_C)
	{
		data->cam->ang_x = -1.570796;
		data->cam->ang_y = -1.570796;
		data->cam->var = 0;
	}
	else if (key == K_V)
		data->cam->var = 1;
}

int	close_win(void *param)
{
	free_struct(param);
	exit(0);
	return (0);
}

void	change_zoom(int key, t_fdf *data)
{
	if (key == K_R)
		data->cam->zoom = data->cam->zoom_def;
	else if (key == K_MINUS)
		data->cam->zoom -= 1;
	else if (key == K_PLUS)
		data->cam->zoom += 1;
}

void	change_shift(int key, t_fdf *data)
{
	static int		sft = 10;

	if (key == K_LT)
		data->cam->align_x -= sft;
	else if (key == K_RT)
		data->cam->align_x += sft;
	else if (key == K_UP)
		data->cam->align_y -= sft;
	else if (key == K_DOWN)
		data->cam->align_y += sft;
	else if (key == K_T)
	{
		data->cam->align_x = WIDTH / 2;
		data->cam->align_y = HEIGHT / 2;
	}
}
