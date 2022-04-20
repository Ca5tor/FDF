/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 02:04:39 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/28 13:34:24 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_free_map_m_z(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->m_height)
		free(map->m_z[i++]);
	free(map->m_z);
}

static void	_check_arg(int arg, char *s)
{
	int	len;

	if (arg != 2 && write(1, FMT404, 27))
		exit(1);
	len = ft_strlen(s) - 4;
	if ((len == 0 || !ft_strnstr(&s[len], ".fdf", 4)) && write(1, FMT404, 27))
		exit(1);
}

static int	_deal_key(int key, t_fdf *data)
{
	if (data->cam->zoom < 1)
		data->cam->zoom = 1;
	else if (key == K_Z || key == K_X || key == K_C || key == K_V)
		change_proj(key, data);
	else if (key == K_Q || key == K_A || key == K_W || \
		key == K_S || key == K_E || key == K_D)
		rotate_xyz(key, data);
	else if (key == K_R || key == K_MINUS || key == K_PLUS)
		change_zoom(key, data);
	else if (key == K_LT || key == K_RT || key == K_UP || \
		key == K_DOWN || key == K_T)
		change_shift(key, data);
	else if (key == ESC)
		close_win(data);
	draw(data);
	return (0);
}

void	free_struct(t_fdf *data)
{
	if (data->cam != NULL)
		free(data->cam);
	else if (data->map != NULL)
	{
		_free_map_m_z(data->map);
		free(data->map);
	}
	else if (data->dot != NULL)
		free(data->dot);
	else if (data->mlx != NULL)
	{
		free(data->mlx->p_addr);
		free(data->mlx->p_img);
		free(data->mlx->p_win);
		free(data->mlx->p_mlx);
		free(data->mlx);
	}
	else if (data != NULL)
		free(data);
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	_check_arg(argc, argv[1]);
	data = fdf_init();
	read_file(data, argv[1]);
	data->mlx = t_mlx_init(data);
	data->cam = cam_init(data);
	draw(data);
	mlx_hook(data->mlx->p_win, 2, (1L << 0), _deal_key, data);
	mlx_hook(data->mlx->p_win, 17, 0, close_win, data);
	mlx_loop(data->mlx->p_mlx);
	return (0);
}
