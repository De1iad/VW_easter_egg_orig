/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:02:37 by obibby            #+#    #+#             */
/*   Updated: 2023/01/28 00:06:17 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../car.h"

void	put_pixel(t_image *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->line_size + x * (img->bpp / 8));
	*(int*)dst = colour;
	//printf("HERE2\n");
}

int	get_pixel_colour(t_image *img, int x, int y)
{
	int	colour;

	colour = *(int *)(img->addr + y % 480 * img->line_size
			+ x % 538 * (img->bpp / 8));
	//printf("HERE1\n");
	return (colour);
}

void	put_image(t_image *dest, t_image *src)
{
	int	x;
	int	y;
	int	colour;

	x = -1;
	while (++x < 538)
	{
		y = -1;
		while (++y < 480)
		{
			colour = get_pixel_colour(src, x, y);
			put_pixel(dest, x, y, colour);
		}
	}
}

int	colourshift(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	rear_right_main(t_car *car)
{
	int	x;
	int	y;
	int	f;

	f = 35;
	y = 122;
	while (++y < 200)
	{
		x = 340 - f;
		while (++x < 340)
			put_pixel(&car->image, x, y, colourshift(255 * (1 - car->strength_rear), 252, 3, 3));
		f++;
	}
	return (0);
}

int	rear_left_main(t_car *car)
{
	int	x;
	int	y;
	int	f;

	f = 475;
	y = 122;
	while (++y < 200)
	{
		x = 440;
		while (++x < f)
			put_pixel(&car->image, x, y, colourshift(255 * (1 - car->strength_rear), 252, 3, 3));
		f++;
	}
	return (0);
}

int	front_right_main(t_car *car)
{
	int	x;
	int	y;
	int	f;

	f = 233;
	y = 122;
	while (++y < 200)
	{
		x = 203;
		while (++x < f)
			put_pixel(&car->image, x, y, colourshift(255 * (1 - car->strength_front), 252, 236, 3));
		f++;
	}
	return (0);
}

int	front_left_main(t_car *car)
{
	int	x;
	int	y;
	int	f;

	f = 30;
	y = 122;
	while (++y < 200)
	{
		x = 90 - f;
		while (++x < 90)
			put_pixel(&car->image, x, y, colourshift(255 * (1 - car->strength_front), 252, 236, 3));
		f++;
	}
	return (0);
}

int	temp_main_func(t_car *car)
{
	mlx_clear_window(car->mlx, car->window);
	mlx_put_image_to_window(car->mlx, car->window, car->xpm.img, 0, 0);
	mlx_put_image_to_window(car->mlx, car->window, car->image.img, 0, 0);
	put_image(&car->image, &car->xpm);
	rear_left_main(car);
	rear_right_main(car);
	front_left_main(car);
	front_right_main(car);
	return (0);
}

int ft_free(t_car *car)
{
	mlx_destroy_image(car->mlx, car->image.img);
	mlx_destroy_image(car->mlx, car->xpm.img);
	mlx_destroy_window(car->mlx, car->window);
	// mlx_destroy_display(car->mlx);
	exit(0);
}

int	key_press(int keycode, t_car *car)
{
	if (keycode == KEY_ESC)
		ft_free(car);
	else if (keycode == KEY_UP)
	{
		if (car->strength_front < 0.8)
			car->strength_front += 0.05;
	}
	else if (keycode == KEY_DOWN)
	{
		if (car->strength_front > 0.05)
			car->strength_front -= 0.05;
	}
	else if (keycode == KEY_RIGHT)
	{
		if (car->strength_rear < 0.8)
			car->strength_rear += 0.05;
	}
	else if (keycode == KEY_LEFT)
	{
		if (car->strength_rear > 0.05)
			car->strength_rear -= 0.05;
	}
	return (0);
}

void	init_vars(t_car *car)
{
	car->strength_front = 0.01;
	car->strength_rear = 0.01;
}

int	main()
{
	t_car car;
	int x;
	int y;

	init_vars(&car);
	car.mlx = mlx_init();
	car.window = mlx_new_window(car.mlx, 538, 480, "VW Easter Egg Demo");
	car.image.img = mlx_new_image(car.mlx, 538, 480);
	car.image.addr = mlx_get_data_addr(car.image.img, &car.image.bpp, &car.image.line_size, &car.image.endian);
	car.xpm.img = mlx_xpm_file_to_image(car.mlx, "images/car.xpm", &x, &y);
	car.xpm.addr = mlx_get_data_addr(car.xpm.img, &car.xpm.bpp, &car.xpm.line_size, &car.xpm.endian);
	mlx_put_image_to_window(car.mlx, car.window, car.xpm.img, 0, 0);
	mlx_hook(car.window, 17, 0, ft_free, &car);
	mlx_hook(car.window, 2, 1L << 0, key_press, &car);
	mlx_loop_hook(car.mlx, temp_main_func, &car);
	mlx_loop(car.mlx);
}