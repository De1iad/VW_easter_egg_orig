/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:03:35 by obibby            #+#    #+#             */
/*   Updated: 2023/01/27 22:29:47 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_mms/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#ifdef __APPLE__
	#define KEY_ESC 53
		// KEY_W = 119,
		// KEY_A = 97,
		// KEY_S = 115,
		// KEY_D = 100,
	#define KEY_UP 126
	#define	KEY_LEFT 123
	#define KEY_RIGHT 124
	#define	KEY_DOWN 125
		// KEY_TAB = 65289,
		// KEY_SHIFT = 65505,
#else
	#define	KEY_ESC 65307
		// KEY_W = 119,
		// KEY_A = 97,
		// KEY_S = 115,
		// KEY_D = 100,
	#define KEY_UP 65362
	#define KEY_LEFT 65361
	#define	KEY_RIGHT 65363
	#define	KEY_DOWN 65364
		// KEY_TAB = 65289,
		// KEY_SHIFT = 65505,
#endif

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
	t_image	image;
	double	strength_front;
	double	strength_rear;
} t_car;