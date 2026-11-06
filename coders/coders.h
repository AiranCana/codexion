/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 10:13:11 by acanadil          #+#    #+#             */
/*   Updated: 2026/11/06 16:16:30 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef enum e_state
{
	IDLE,
	FINISH,
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

typedef struct s_USB
{
	int				id;
	long long		cooldown_start;
	int				fre;
	pthread_mutex_t	mutex;
}	t_USB;

typedef struct s_data
{
	int				num_coders;
	long long		time_to_burnout;
	long long		time_to_compile;
	long long		time_to_debug;
	long long		time_to_refactor;
	int				number_of_compiles_required;
	long long		dongle_cooldown;
	t_schedule		scheduler;
}	t_data;

typedef struct s_coder
{
	pthread_t	thread_id;
	t_USB		*right_usb;
	t_USB		*left_usb;
	long long	first_compile_start;
	long long	last_compile_start;
	int			compile_count;
	int			bornout_log;
	int			coder_id;
	t_table		*table;
	t_state		state;
	t_data		*data;
}	t_coder;

typedef struct s_list_text
{
	int					id;
	long long			time;
	char				*text;
	struct s_list_text	*next;
	struct s_list_text	*prev;
}	t_text;

typedef struct s_table
{
	pthread_t		thread_id;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_coder			**coders;
	t_text			*text;
	int				failed;
}	t_table;

int			printer_error(char *message);
void		printer_coder(t_coder *coder);
long long	get_time(void);
int			ft_sleep(long long time, t_coder **coder);
int			verif_time(long long data_time);
int			priority(t_coder *this_coder, t_table *table);
void		*ruotine(void *arg);
void		*rutine_table(void *arg);
void		print_coder(t_coder *coder);
void		asign_usb(t_USB **usb, t_coder **coders);
int			available_usbs(t_coder *coder);
void		wait_codex(t_table *table, int i);
int			start_routin(t_table *table);
void		wait_time(t_coder *coder);
int			all_coders_finish(t_table *table);
int			found_dead(t_table *table);
int			verif_bornout(t_coder *coder);
void		add_first_text(t_coder *coder, char *text, long long time, int id);
t_text		*get_min_time_text(t_table *table);
void		free_texts(t_table *table);
int			prube_scheduler(t_data *data, t_coder *this_coder, t_coder *coder);
int			print_text(t_table *table);
int			veif_priority(t_coder *this, t_data *data, t_coder *coder);
void		asign_state(t_coder *coder, int state);

#endif