/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:24 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/25 14:15:01 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_eol(int pid)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		usleep(100);
		i++;
	}
}

static void	ft_send_message(int pid, char *message)
{
	char	c;
	int		i;

	while (*message)
	{
		i = 7;
		while (i > -1)
		{
			c = *message;
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			i--;
			usleep(100);
		}
		message++;
	}
	ft_send_eol(pid);
}

int	main(int ac, char **av)
{
	if (ac != 3)
		ft_putstr_fd("usage: ./client [server-pid] [message]\n", 1);
	if (ac == 3)
	{
		ft_send_message(ft_atoi(av[1]), av[2]);
	}
	return (0);
}
