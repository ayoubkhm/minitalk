/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhamass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:32:38 by akhamass          #+#    #+#             */
/*   Updated: 2024/04/25 18:49:45 by akhamass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void	ft_handler(int signal, siginfo_t *info, void *s)
{
	static char	buffer[BUFFER_SIZE];
	static int	bit = 0;
	static int	i = 0;
	static int	index = 0;	

	if (signal == SIGUSR1)
	{
		i |= (0x01 << bit);
	}
	(void)s;
	bit++;
	if (bit == 8)
	{
		buffer[index++] = (char)i;
		if (index == BUFFER_SIZE - 1 || i == '\n')
		{
			buffer[index] = '\0';
			ft_printf("%s", buffer);
			index = 0;
		}
		bit = 0;
		i = 0;
		kill(info->si_pid, SIGUSR2);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sig;

	if (argc != 1)
	{
		ft_printf("Error: wrong format. Try <./server> instead \n");
		return (0);
	}
	(void)argv;
	pid = getpid();
	ft_printf("PID = %d\n", pid);
	sig.sa_sigaction = ft_handler;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
