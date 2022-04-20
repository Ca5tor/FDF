/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:28:56 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/28 11:42:50 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_terminette(t_fdf *data, int *fd, int flag)
{
	if (flag == 0)
		write(1, FD404, 30);
	else if (flag == 1)
		write(1, FILE404, 22);
	close(*fd);
	free_struct(data);
	exit(1);
}

void	check_file(t_fdf *data, char *str)
{
	char	*temp_line;
	int		fd;

	fd = open(str, O_RDONLY, 0);
	if (((fd < 0 || read(fd, NULL, 0) < 0)))
		_terminette(data, &fd, 0);
	temp_line = get_next_line(fd);
	if (!temp_line)
	{
		free(temp_line);
		_terminette(data, &fd, 1);
	}
	close(fd);
	free(temp_line);
}

double	find_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	find_min(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

double	mod(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}
