/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_brake.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:37:13 by obibby            #+#    #+#             */
/*   Updated: 2023/02/12 23:38:04 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../car.h"

int	brake_lights_rear(t_car *car)
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

void	brake_lights(t_car *car)
{
	brake_lights_rear(car);
}
