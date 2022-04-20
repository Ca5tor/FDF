/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_Initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 03:10:42 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/28 10:25:10 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*map_init(t_fdf *data)
{
	t_map	*new_map;

	new_map = (t_map *)malloc(sizeof(t_map));
	if (!new_map && write(1, MEMORY404, 29))
	{
		free_struct(data);
		exit(1);
	}
	return (new_map);
}

t_dot	*dot_init(t_fdf *data)
{
	t_dot	*new_dot;

	new_dot = (t_dot *)malloc(sizeof(t_dot) * data->map->m_size + 1);
	if (!new_dot && write(1, MEMORY404, 29))
	{
		free_struct(data);
		exit(1);
	}
	fill_dot(data, new_dot);
	return (new_dot);
}

t_cam	*cam_init(t_fdf *data)
{
	t_cam	*new_cam;
	int		zoom_width;
	int		zoom_height;

	new_cam = (t_cam *)malloc(sizeof(t_cam));
	if (!new_cam && write(1, MEMORY404, 29))
	{
		free_struct(data);
		exit(1);
	}
	zoom_width = (WIDTH / data->map->m_width) / 2;
	zoom_height = (HEIGHT / data->map->m_height) / 2;
	new_cam->zoom_def = find_min(zoom_width, zoom_height);
	new_cam->zoom = new_cam->zoom_def;
	new_cam->ang_x = 0;
	new_cam->ang_y = 0;
	new_cam ->ang_z = 0;
	new_cam->align_x = WIDTH / 2;
	new_cam->align_y = HEIGHT / 2;
	new_cam->var = 0;
	return (new_cam);
}

t_mlx	*t_mlx_init(t_fdf *data)
{
	t_mlx	*new_mlx;

	new_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!new_mlx && write(1, MEMORY404, 29))
	{
		free_struct(data);
		exit(1);
	}
	new_mlx->p_mlx = mlx_init();
	new_mlx->p_win = mlx_new_window(new_mlx->p_mlx, WIDTH, HEIGHT, "FDF");
	new_mlx->p_img = mlx_new_image(new_mlx->p_mlx, WIDTH, HEIGHT);
	new_mlx->p_addr = mlx_get_data_addr(new_mlx->p_img, &(new_mlx->bpp),
			&(new_mlx->len), &(new_mlx->endian));
	ft_bzero(new_mlx->p_addr, WIDTH * HEIGHT * (new_mlx->bpp / 8));
	return (new_mlx);
}

t_fdf	*fdf_init(void)
{
	t_fdf	*new_data;

	new_data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!new_data && write(1, MEMORY404, 29))
		exit(1);
	return (new_data);
}
