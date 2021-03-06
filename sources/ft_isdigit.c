/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:02:12 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/27 18:28:01 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/**
 * La fonction ft_isdigit() vérifie que c
 * est un chiffre (de 0 à 9).
 *
 * \param	c	Un caractère non-signé.
 * \return		Un entier à valeur booléenne.
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
