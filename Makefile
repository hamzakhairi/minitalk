# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/28 12:01:58 by hkhairi           #+#    #+#              #
#    Updated: 2025/02/28 17:31:32 by hkhairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME_CLIENT = client
NAME_SERVER = server
HEADER_FILE = minitalk.h

HELP_FILE = utile.c
SRC_CLIENT = client.c
SRC_SERVER = server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_HELP = $(HELP_FILE:.c=.o)

all: client server

client: $(OBJ_CLIENT) $(OBJ_HELP)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(OBJ_HELP) -o $(NAME_CLIENT)

server: $(OBJ_SERVER) $(OBJ_HELP)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(OBJ_HELP) -o $(NAME_SERVER)

%.o: %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_HELP)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all
