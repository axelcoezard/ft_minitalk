/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:05:35 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/25 14:36:31 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * Affiche sur la sortie standard le pid passe
 * en parametre.
 *
 * \param	pid	Le pid a afficher.
 */
static void	ft_print_pid(int pid)
{
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
}

/**
 * Execute lors de la reception dun SIGUSR1 ou SIGUSR2,
 * la fonction ft_catch_signal interprete les signaux entrants
 * et les traduit en caracteres consecutifs qu'elle affiche.
 *
 * \param	sig_id	L'id du signal recu.
 */
static void	ft_catch_signal(int sig_id)
{
	static unsigned char	c = 0;
	static int				i = 0;

	i += 1;
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
	ft_print_pid(getpid());
	signal(SIGUSR1, ft_catch_signal);
	signal(SIGUSR2, ft_catch_signal);
	while (1)
		pause();
	return (0);
}
