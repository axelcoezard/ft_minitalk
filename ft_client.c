/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:36:24 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/25 23:28:55 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * La fonction ft_print_message permet d'ecrire
 * sur la sortie standard un message contenant un status (sent/received),
 * le PID de l'expediteur et le poid en octets du message.
 *
 * \param	pid		Le PID du processus expediteur.
 * \param	type	MESSAGE_SENT ou MESSAGE_RECEIVED.
 * \param	size	Le poid du message.
 */
static void	ft_print_message(int pid, int type, int size)
{
	if (type == MESSAGE_SENT)
		ft_putstr_fd("Sent", 1);
	if (type == MESSAGE_RECEIVED)
		ft_putstr_fd("Received", 1);
	ft_putstr_fd(" message (", 1);
	ft_putnbr_fd(size, 1);
	ft_putstr_fd("bits) to/from process ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd(".\n", 1);
}

/**
 * La fonction ft_receive_message permet d'affiche un
 * message de reception sur la sortie standard lorsque
 * le client recoit un signal de confirmation du server.
 * la fonction compte egalement le nombre de bits recu
 * par le serveur.
 *
 * \param	sig_id
 * \param	info
 * \param	context
 */
static void	ft_receive_message(int sig_id, siginfo_t *info, void *context)
{
	static int	bits = 0;

	(void) context;
	if (sig_id == SIGUSR2)
		bits += 1;
	if (sig_id == SIGUSR1)
	{
		ft_print_message(info->si_pid, MESSAGE_RECEIVED, bits);
		exit(EXIT_SUCCESS);
	}
}

/**
 * La fonction ft_send_end envoie a un processus (via son pid)
 * 8 signaux SIGUSR1 qui correspondent aux bits du caractere nul '\0'.
 *
 * \param	pid		Le pid du processus destination.
 */
static void	ft_send_end(int pid)
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
	ft_send_end(pid);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	unsigned int		pid;

	if (ac != 3)
	{
		ft_putstr_fd("usage: ./client [server-pid] [message]\n", 1);
		return (EXIT_ERROR);
	}
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_receive_message;
	pid = ft_atoi(av[1]);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_print_message(pid, MESSAGE_SENT, (ft_strlen(av[2]) + 1) * 8);
	ft_send_message(pid, av[2]);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
