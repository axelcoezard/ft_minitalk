/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:05:35 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/25 13:51:27 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_print_pid(int pid)
{
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
}

static void	ft_handle_signal(int sig_id)
{
	static unsigned char	c = 0;
	static int				i = 0;

	i = i + 1;
	c |= sig_id == SIGUSR2;
	if (i != 8)
		c <<= 1;
	if (i == 8)
	{
		if (c == 0)
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	pid_t pid = getpid();

	ft_print_pid(pid);
	signal(SIGUSR1, ft_handle_signal);
	signal(SIGUSR2, ft_handle_signal);
	while (1)
		pause();
	return (0);
}
