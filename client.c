/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhamass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:10:47 by akhamass          #+#    #+#             */
/*   Updated: 2024/04/25 18:32:02 by akhamass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

static void	ft_confirm(int signal)
{
	(void)signal;
}

void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

void	send_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		signal(SIGUSR1, ft_confirm);
		signal(SIGUSR2, ft_confirm);
		ft_send_bits(pid, message[i]);
		i++;
	}
	ft_send_bits(pid, '\n');
}

int	validate_input(int argc, char **argv, int *pid)
{
	if (argc != 3 || ft_strlen(argv[2]) == 0)
	{
		ft_printf("Error: wrong format or empty message.\n");
		return (0);
	}
	*pid = ft_atoi(argv[1]);
	if (*pid <= 1)
	{
		ft_printf("Error: Invalid PID. PID must be greater than 1.\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (!validate_input(argc, argv, &pid))
	{
		return (1);
	}
	send_message(pid, argv[2]);
	return (0);
}
