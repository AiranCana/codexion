/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 10:13:11 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/18 12:57:15 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

# include <pthread.h>
# include <unistd.h>

typedef enum e_state
{
	IDLE,
	COMPILING,
	DEBUGGING,
	REFACTORING,
	BURNED_OUT
}	t_state;

typedef enum e_schedule
{
	FIFO,
	EDF
}	t_schedule;

typedef struct s_data
{
	long long		time_to_burnout;
	long long		time_to_compile;
	long long		time_to_debug;
	long long		time_to_refactor;
	int				number_of_compiles_required;
	long long		dongle_cooldown;
	t_schedule		scheduler;
	pthread_mutex_t	log_mutex;
}	t_data;

typedef struct s_coder
{
	pthread_t	thread_id;
	long long	last_compile_start;
	int			coder_id;
	t_state		state;
	t_data		*data;
}	t_coder;

void	*delet_coders(t_coder **coder);
t_coder	*gen_coder(int coder_id, t_data *data);
t_coder	**init_coders(int argc, char **argv);
t_data	*init_data(int argc, char **args);
int		printer_error(char *message);

#endif