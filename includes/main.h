/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:16:53 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/14 16:38:23 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

void	ft_print_world(t_world w);
void	my_mlx_pixel_put(t_info *data, int x, int y, int color);
int		ft_convert_color(t_color c);
void	ft_draw(t_info *vars, t_canvas canvas);
int		close_win(int keycode, t_info *vars);
int		close_win_2(int keycode, t_info *vars);

#endif