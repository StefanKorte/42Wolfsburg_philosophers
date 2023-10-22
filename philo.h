/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:48:57 by skorte            #+#    #+#             */
/*   Updated: 2022/04/15 19:59:34 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>
/*
** Allowed external functions:
**
** memset, printf, malloc, free, write,
** usleep, gettimeofday, pthread_create,
** pthread_detach, pthread_join, pthread_mutex_init,
** pthread_mutex_destroy, pthread_mutex_lock,
** pthread_mutex_unlock
**
** stdlib.h for malloc and free
** unistd.h for write
*/

# ifndef MICROSECONDS
#  define MICROSECONDS 0
# endif

struct	s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	unsigned long	starttime;
	int				philos_still_eating;
	pthread_mutex_t	*philos_still_eating_mutex;
	pthread_mutex_t	*fork_mutex;
};

struct	s_phdata
{
	int				philo_num;
	int				fork_1;
	int				fork_2;
	char			*str_taken;
	char			*str_eating;
	char			*str_sleeping;
	char			*str_thinking;
	char			*str_died;
	struct s_data	*data;
	int				meal_num;
	unsigned long	last_eaten;
	pthread_mutex_t	*last_eaten_mutex;
};

// philo.c
void			*ft_philo_thread(void *ptr);

// ft_simulation.c
void			ft_begin_simulation(pthread_t **philo,
					struct s_data *data, struct s_phdata **phdata);
void			ft_check_death(struct s_data *data, struct s_phdata **phdata);
void			ft_end_simulation(pthread_t **philo, struct s_data *data);

// ft_free.c
void			ft_free(pthread_t **t, struct s_data *d, struct s_phdata **p);

// Utils:
// ft_conversion_utils.c
int				ft_atoi(char *nptr);
char			*ft_ultoa(unsigned long n);

// ft_string_utils.c
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_3(char const *s1, char const *s2, char const *s3);
size_t			ft_strlen(const char *s);

// ft_time.c
unsigned long	ft_time_us(void);

// ft_write.c
void			ft_write(unsigned long time, const char *str,
					struct s_data *data);
void			ft_write_no_test(unsigned long time, const char *str,
					struct s_data *data);

// ft_actions.c
void			ft_sleeping(struct s_phdata *phdata);
void			ft_thinking(struct s_phdata *phdata);
void			ft_eating(struct s_phdata *phdata);
void			ft_grab_forks(struct s_phdata *phdata);
void			ft_release_forks(struct s_phdata *phdata);

// ft_mutex.c
void			ft_update_last_eaten(struct s_phdata *phdata,
					unsigned long start);
int				ft_still_eating_get(struct s_data *data);
int				ft_still_eating_minus(struct s_data *data);
int				ft_died(struct s_data *data, unsigned long time, char *str);
int				ft_is_this_philo_dead(struct s_phdata *phdata,
					unsigned long time);

// ft_init.c
struct	s_data	*ft_init_data(int argc, char *argv[]);
struct	s_phdata	*ft_init_phdata(int phnum, struct s_data *data);

#endif