/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:10:52 by obibby            #+#    #+#             */
/*   Updated: 2023/02/12 23:26:50 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../car.h"

// draw front right light to image.
void	front_right_main(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 25;
	y = 130;
	x_base = 310;
	if (!EasterEggLightsEE.FrontLightRight)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.FrontLightRightPWM * 0.0008;
	while (++y < 250)
	{
		x = x_base - (x_length * 0.5);
		while (++x < x_length + x_base)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		x_length++;
	}
}

// draw front left light to image.
void	front_left_main(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 25;
	x_base = 145;
	y = 130;
	if (!EasterEggLightsEE.FrontLightLeft)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.FrontLightLeftPWM * 0.0008;
	while (++y < 250)
	{
		x = x_base - x_length;
		while (++x < x_base + (x_length * 0.5))
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		x_length++;
	}
}

void	main_lights(t_car *car)
{
	front_left_main(car);
	front_right_main(car);
}
