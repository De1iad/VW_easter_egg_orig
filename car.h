/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:03:35 by obibby            #+#    #+#             */
/*   Updated: 2023/01/27 16:43:36 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_linux/mlx.h"
#include <stdlib.h>
#include <unistd.h>

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
} t_image;

typedef struct s_car
{
	void	*mlx;
	void	*window;
	t_image	xpm;
	void	*image;
} t_car;