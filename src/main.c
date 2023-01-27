/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:02:37 by obibby            #+#    #+#             */
/*   Updated: 2023/01/27 16:42:39 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../car.h"

int	main()
{
	t_car car;
	int x;
	int y;

	car.mlx = mlx_init();
	car.window = mlx_new_window(car.mlx, 854, 480, "VW Easter Egg Demo");
	//car.image = mlx_new_image(car.mlx, 854, 480);
	car.xpm.img = mlx_xpm_file_to_image(car.mlx, "images/car.xpm", &x, &y);
	mlx_put_image_to_window(car.mlx, car.window, car.xpm.img, x, y);
	pause();
}