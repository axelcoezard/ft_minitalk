/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:24 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/29 14:02:59 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/**
 * La fonction ft_receive_message permet de fermer le programme
 * a la reception d'un signal SIGUSR1.
 *
 * \param	sig_id	id du signal
 */
static void	ft_receive_message(int sig_id)
{
	if (sig_id == SIGUSR1)
		exit(EXIT_SUCCESS);
}

/**
 * La fonction ft_send_char permet d'envoyer un caractere unique via
 * les signaux SIGUSR1 et SIGUSR2.
 *
 * \param	pid	Le pid du server cible.
 * \param	c	Le caractere a envoyer.
 */
static void	ft_send_char(int pid, char c)
{
	int		i;

	i = 7;
	while (i > -1)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		pause();
		usleep(200);
	}
}

/**
 * La fonction ft_send_message envoie a un processus (via son pid)
 * une chaine de caractere. Les caracteres de cette chaine sont
 * lus bit a bit, et envoye un par un.
 *
 * \param	pid		Le pid du processus destination.
 * \param	message	La chaine de caracteres a envoyer.
 */
static void	ft_send_message(int pid, char *message)
{
	while (*message)
	{
		ft_send_char(pid, *message);
		message++;
	}
	ft_send_char(pid, '\n');
}

static int	ft_verify_pid(int pid)
{
	int	i;

	i = 8;
	while (kill(pid, SIGUSR1) == 0 && i--)
	{
		pause();
		usleep(200);
	}
	if (i != -1)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	unsigned int	pid;

	if (ac != 3)
	{
		ft_putstr_fd("Usage: ./client [server-pid] [message]\n", 1);
		return (EXIT_ERROR);
	}
	pid = ft_atoi(av[1]);
	signal(SIGUSR1, ft_receive_message);
	signal(SIGUSR2, ft_receive_message);
	if (!ft_verify_pid(pid))
	{
		ft_putstr_fd("Invalid PID\n", 1);
		return (EXIT_ERROR);
	}
	ft_send_message(pid, av[2]);
	return (EXIT_SUCCESS);
}
