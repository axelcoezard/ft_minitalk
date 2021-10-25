/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:05:35 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/25 10:57:40 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handleSignal(int pid)
{
	(void) pid;
}

int	main(void)
{
	pid_t pid = getpid();

	ft_putnbr_fd(pid, 1);
	signal(SIGUSR1, handleSignal);
	signal(SIGUSR2, handleSignal);
	while (1)
		pause();
	return (0);
}
