/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:28:35 by hkhairi           #+#    #+#             */
/*   Updated: 2025/03/01 13:11:30 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int validation_pid(char *pid)
{
    int i = 0;

    while (pid[i])
    {
        if ((pid[i] < '0') || (pid[i] > '9'))
            return (0);
        i++;
    }
    return 1;
}

void send_character(pid_t server_pid, char character)
{
    int i;

    i = 0;
    while (i < 8)
    {
        if (character & (1 << i))
            kill(server_pid, SIGUSR1);
        else
            kill(server_pid, SIGUSR2);
        usleep(600);
        i++;
    }
}

void send_message(pid_t server_pid, char *mesage)
{
    size_t i;
    
    i = 0;
    while (mesage[i])
    {
        send_character(server_pid, mesage[i]);
        i++;
    }
    send_character(server_pid, '\0');
}

int main(int argc, char **argv)
{
    pid_t server_pid;
    if (argc != 3 || argv[1][0] == '\0' || argv[2][0] == '\0')
    {
        put_str("Usage: ./client <server_pid> <message>\n");
        return (1);
    }
    if (!validation_pid(argv[1]))
    {
        put_str("incorecte PID\n");
        return (1);
    }
    server_pid = ft_atoi(argv[1]);
    send_message(server_pid, argv[2]);

    return (0);
}
