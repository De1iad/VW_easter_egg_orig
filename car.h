/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:03:35 by obibby            #+#    #+#             */
/*   Updated: 2023/01/28 19:19:37 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_mms/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#ifdef __APPLE__
	#define KEY_ESC 53
	#define KEY_UP 126
	#define	KEY_LEFT 123
	#define KEY_RIGHT 124
	#define	KEY_DOWN 125
	#define	KEY_F 3
	#define KEY_R 15
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
	void	*mlx; // the mlx pointer.
	void	*window; // pointer to the active window.
	t_image	xpm; // xpm image of the car.
	t_image	image; // image used to buffer before pushing to window.
	int	front_lights; // lights off == 0, lights on == 1.
	int	rear_lights; // lights off == 0, lights on == 1.
	unsigned short	strength_front; // intensity of the light, 0-1000.
	unsigned short	strength_rear; // intensity of the light, 0-1000.
} t_car;