/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:02:37 by obibby            #+#    #+#             */
/*   Updated: 2023/02/12 23:37:03 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../car.h"

inputsEE EasterEggLightsEE;

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// puts frames per second to window, based on time to draw last frame.
void	put_fps(t_car *car)
{
	char	*tmp;
	char	*str;

	tmp = ft_itoa(1000 / (car->current_time - car->previous_time));
	str = ft_strjoin(tmp, "fps");
	free(tmp);
	mlx_string_put(car->mlx, car->window, 5, 10, colourshift(255, 0, 0, 0), str);
	free(str);
}

// puts car image and light image to window, updates light image with new values.
int	light_loop(t_car *car)
{
	car->current_time = get_time_in_ms();
	if (car->current_time - car->previous_time >= 10)
	{
		//EasterEgg_Cyclic_10ms();
		brake_lights(car);
		main_lights(car);
		fog_lights(car);
		parking_lights(car);
		indicators(car);
		mlx_put_image_to_window(car->mlx, car->window, car->image.img, 0, 0);
		mlx_put_image_to_window(car->mlx, car->window, car->alpha_image.img, 0, 0);
		put_fps(car);
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
	else if (keycode == KEY_UP)
	{
		if (EasterEggLightsEE.ParkingLightLeft)
			EasterEggLightsEE.ParkingLightLeft = 0;
		else
			EasterEggLightsEE.ParkingLightLeft = 1;
		EasterEggLightsEE.ParkingLightLeftPWM = 500;
		if (EasterEggLightsEE.ParkingLightRight)
			EasterEggLightsEE.ParkingLightRight = 0;
		else
			EasterEggLightsEE.ParkingLightRight = 1;
		EasterEggLightsEE.ParkingLightRightPWM = 500;
	}
	else if (keycode == KEY_DOWN)
	{
		if (EasterEggLightsEE.FrontLightLeft)
			EasterEggLightsEE.FrontLightLeft = 0;
		else
			EasterEggLightsEE.FrontLightLeft = 1;
		EasterEggLightsEE.FrontLightLeftPWM = 500;
		if (EasterEggLightsEE.FrontLightRight)
			EasterEggLightsEE.FrontLightRight = 0;
		else
			EasterEggLightsEE.FrontLightRight = 1;
		EasterEggLightsEE.FrontLightRightPWM = 500;
	}
	else if (keycode == KEY_F)
	{
		if (EasterEggLightsEE.FogLights)
			EasterEggLightsEE.FogLights = 0;
		else
			EasterEggLightsEE.FogLights = 1;
		EasterEggLightsEE.FogLightsPWM = 500;
	}
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
