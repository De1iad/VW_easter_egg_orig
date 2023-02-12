/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:03:35 by obibby            #+#    #+#             */
/*   Updated: 2023/02/12 20:20:22 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAR_H
# define CAR_H

# include "minilibx_linux/mlx.h"
# include "EasterEgg.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

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
	#define	KEY_F 102
	#define	KEY_R 114
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
	t_image	alpha_image;
	time_t	current_time;
	time_t	previous_time;
	time_t	loop_time;
} t_car;

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);

#endif
