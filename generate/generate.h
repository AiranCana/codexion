/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:58:14 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/23 12:59:00 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATE_H
# define GENERATE_H

# include "../coders.h"

void	*delet_coders(t_coder **coder);
t_coder	*gen_coder(int coder_id, t_data *data);
t_coder	**init_coders(int argc, char **argv);
t_data	*init_data(int argc, char **args);
t_USB	**gen_usbs(size_t num);
void	*delet_usbs(t_USB **usb);
void	asign_usb(t_USB **usb, t_coder **coders);
t_table	*gen_table(t_coder **coders);
void	delete_table(t_table *table);

// void	print_all_coders(t_coder **coders);

#endif