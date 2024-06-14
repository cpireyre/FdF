/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:26:43 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/14 10:02:47 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c);

int	ft_atoi(const char *str)
{
	long	nbr;
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = (*str != '-') - (*str == '-');
	if (*str == '-' || *str == '+')
		str++;
	nbr = 0;
	while ('0' <= *str && *str <= '9')
		nbr = nbr * 10 + *str++ - '0';
	return (sign * (int)nbr);
}

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}
