/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 01:29:18 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/28 13:32:13 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <fcntl.h>
# include "../utils/GNL/get_next_line.h"
# include "../utils/LIBFT/libft.h"
# include "../mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>

/*	shift map	*/
# define K_LT 65361
# define K_RT 65363
# define K_UP 65362
# define K_DOWN 65364
# define K_T 116
/*	rotate map on xyz	*/
# define K_Q 113
# define K_A 97
# define K_W 119
# define K_S 115
# define K_E 101
# define K_D 100
/*	put back in place z*/
# define K_R 114
/*	exit programm	*/
# define ESC 65307
/*	zoom	*/
# define K_MINUS 65453
# define K_PLUS 65451
/*	projection TOP FRONT SIDE ISO	*/
# define K_Z 122
# define K_X 120
# define K_C 99
# define K_V 118
/*	size window	*/
# define WIDTH 1600
# define HEIGHT 900
/*	grid color and background */
# define WHITE	0x005b96
# define RED	0xffffff
# define BACKGROUND 0x404040
/*	messages on error	*/
# define FMT404 "USAGE: ./fdf filename.fdf\n"
# define MEMORY404 "ERROR: memory not allocated\n"
# define FD404 "ERROR: file descriptor error\n"
# define FILE404 "ERROR: file is empty\n"

typedef struct s_map
{
	int	**m_z;
	int	m_width;
	int	m_height;
	int	m_size;
}	t_map;

typedef struct s_dot
{
	double	x;
	double	y;
	int		z;
	int		color;
}	t_dot;

typedef struct s_cam
{
	double	ang_x;
	double	ang_y;
	double	ang_z;
	int		zoom;
	int		align_x;
	int		align_y;
	int		var;
	int		zoom_def;
}	t_cam;

typedef struct s_mlx
{
	void	*p_mlx;
	void	*p_win;
	void	*p_img;
	char	*p_addr;
	int		bpp;
	int		len;
	int		endian;
}	t_mlx;

typedef struct s_fdf
{
	t_map	*map;
	t_dot	*dot;
	t_cam	*cam;
	t_mlx	*mlx;
}	t_fdf;

/*	struct_init.c	*/
t_fdf	*fdf_init(void);
t_map	*map_init(t_fdf *data);
t_dot	*dot_init(t_fdf *data);
t_mlx	*t_mlx_init(t_fdf *data);
t_cam	*cam_init(t_fdf *data);
/*	get_map.c	*/
void	read_file(t_fdf *data, char *str);
/*	checking.c	*/
void	check_file(t_fdf *data, char *str);
/*	main.c	*/
void	free_struct(t_fdf *data);
/*	print_map.c	*/
void	draw(t_fdf *data);
/*	projection.c	*/
t_dot	proj(t_dot *d, t_fdf *data);
/*	utils.c	*/
double	find_max(double a, double b);
double	find_min(double x, double y);
double	mod(double a);
/*	map_utils.c	*/
void	fill_dot(t_fdf *data, t_dot	*new_dot);
void	u_fill_clr(t_fdf *data, char *line);
void	_fill_mtx(int *line_z, char *line);
/*	key_utils.c	*/
void	rotate_xyz(int key, t_fdf *data);
void	change_proj(int key, t_fdf *data);
int		close_win(void *param);
void	change_zoom(int key, t_fdf *data);
void	change_shift(int key, t_fdf *data);

#endif