/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:02:37 by obibby            #+#    #+#             */
/*   Updated: 2023/02/11 13:17:21 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../car.h"

inputsEE EasterEggLightsEE;
// puts a pixel to an image.
void	put_pixel(t_image *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->line_size + x * (img->bpp / 8));
	*(int*)dst = colour;
}

// finds colour of individual pixel in car image.
int	get_pixel_colour(t_image *img, int x, int y)
{
	int	colour;

	colour = *(int *)(img->addr + y % 782 * img->line_size
			+ x % 960 * (img->bpp / 8));                                                                                                                                                                                                                                                                                                                                           
	return (colour);
}

// puts car image to an image, setting alpha to zero.
void	put_image(t_image *dest, t_image *src)
{
	int	x;
	int	y;
	int	colour;

	x = -1;
	while (++x < 960)
	{
		y = -1;
		while (++y < 782)
		{
			colour = get_pixel_colour(src, x, y);
			colour |= 1UL << 24;
			colour |= 1UL << 25;
			colour |= 1UL << 26;
			colour |= 1UL << 27;
			colour |= 1UL << 28;
			colour |= 1UL << 29;
			colour |= 1UL << 30;
			colour |= 1UL << 31;
			put_pixel(dest, x, y, colour);
		}
	}
}

// encodes an int with trgb colour values.
int	colourshift(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// draw brake lights to image.
int	brake_lights(t_car *car)
{
	int	x;
	int	y;
	int	x_length;
	double	alpha;

	x_length = 840;
	y = 130;
	if (!EasterEggLightsEE.BrakeLights)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.BrakeLightsPWM * 0.0008;
	while (++y < 250)
	{
		x = 805;
		while (++x < x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 3 * alpha, 3 * alpha));
		x_length++;
	}
	x_length = 35;
	y = 130;
	while (++y < 250)
	{
		x = 658 - x_length;
		while (++x < 658)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 3 * alpha, 3 * alpha));
		x_length++;
	}
	return (0);
}

void	parking_light_right(t_car *car)
{
	int		x;
	int		y;
	int		i;
	int		x_length;
	double	alpha;

	x_length = 333;
	y = 175;
	if (!EasterEggLightsEE.ParkingLightRight)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.ParkingLightRightPWM * 0.0008;
	i = 0;
	while (++y < 190)
	{
		x = 325 - i;
		while (++x < x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 165 * alpha, 0 * alpha));
		x_length++;
		i++;
	}
}

void	parking_light_left(t_car *car)
{
	int		x;
	int		y;
	int		i;
	int		x_length;
	double	alpha;

	x_length = 155 - 25;
	y = 175;
	if (!EasterEggLightsEE.ParkingLightLeft)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.ParkingLightLeftPWM * 0.0008;
	i = 0;
	while (++y < 190)
	{
		x = 122 - i;
		while (++x < x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 165 * alpha, 0 * alpha));
		x_length++;
		i++;
	}
}

// draw front right light to image.
int	front_right_main(t_car *car)
{
	int		x;
	int		y;
	int		x_length;
	double	alpha;

	x_length = 333;
	y = 130;
	if (!EasterEggLightsEE.FrontLightRight)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.FrontLightRightPWM * 0.0008;
	while (++y < 250)
	{
		x = 303;
		while (++x < x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		x_length++;
	}
	return (0);
}

// draw front left light to image.
int	front_left_main(t_car *car)
{
	int			x;
	int			y;
	int			x_length;
	double		alpha;

	x_length = 30;
	y = 130;
	if (!EasterEggLightsEE.FrontLightLeft)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.FrontLightLeftPWM * 0.0008;
	while (++y < 250)
	{
		x = 152 - x_length;
		while (++x < 152)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		x_length++;
	}
	return (0);
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// puts car image and light image to window, updates light image with new values.
int	light_loop(t_car *car)
{
	mlx_put_image_to_window(car->mlx, car->window, car->image.img, 0, 0);
	mlx_put_image_to_window(car->mlx, car->window, car->alpha_image.img, 0, 0);
	car->current_time = get_time_in_ms();
	if (car->current_time - car->previous_time >= 10)
	{
		EasterEgg_Cyclic_10ms();
		brake_lights(car);
		front_left_main(car);
		front_right_main(car);
		parking_light_left(car);
		parking_light_right(car);
		car->previous_time = car->current_time;
	}
	return (0);
}

// frees all allocated memory and exits.
int ft_free(t_car *car)
{
	mlx_destroy_image(car->mlx, car->image.img);
	mlx_destroy_image(car->mlx, car->alpha_image.img);
	mlx_destroy_display(car->mlx);
	exit(0);
}

// temporary measure for displaying changes in the light and intensity variables.
int	key_press(int keycode, t_car *car)
{
	if (keycode == KEY_ESC)
		ft_free(car);
	// else if (keycode == KEY_UP)
	// {
	// 	EasterEggSequence = 1;
	// 	if (car->strength_front < 950)
	// 		car->strength_front += 50;
	// }
	// else if (keycode == KEY_DOWN)
	// {
	// 	if (car->strength_front > 50)
	// 		car->strength_front -= 50;
	// }
	// else if (keycode == KEY_F)
	// {
	// 	if (car->front_lights)
	// 		car->front_lights = 0;
	// 	else
	// 		car->front_lights = 1;
	// }
	return (0);
}

int	main()
{
	t_car car;
	int x;
	int y;

	car.previous_time = get_time_in_ms();
	car.mlx = mlx_init();
	car.window = mlx_new_window(car.mlx, 960, 782, "VW Easter Egg Demo");
	car.image.img = mlx_new_image(car.mlx, 960, 782);
	car.image.addr = mlx_get_data_addr(car.image.img, &car.image.bpp, &car.image.line_size, &car.image.endian);
	car.xpm.img = mlx_xpm_file_to_image(car.mlx, "images/car.xpm", &x, &y);
	car.xpm.addr = mlx_get_data_addr(car.xpm.img, &car.xpm.bpp, &car.xpm.line_size, &car.xpm.endian);
	put_image(&car.image, &car.xpm);
	mlx_destroy_image(car.mlx, car.xpm.img);
	car.alpha_image.img = mlx_new_image_alpha(car.mlx, 960, 782);
	car.alpha_image.addr = mlx_get_data_addr(car.alpha_image.img, &car.alpha_image.bpp, &car.alpha_image.line_size, &car.alpha_image.endian);
	mlx_hook(car.window, 17, 0, ft_free, &car);
	mlx_hook(car.window, 2, 1L << 0, key_press, &car);
	mlx_loop_hook(car.mlx, light_loop, &car);
	mlx_loop(car.mlx);
}
