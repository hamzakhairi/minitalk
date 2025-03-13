# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/28 12:01:58 by hkhairi           #+#    #+#              #
#    Updated: 2025/03/06 22:41:10 by hkhairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus
HEADER_FILE = minitalk.h

HELP_FILE = utile.c
SRC_CLIENT = client.c
SRC_SERVER = server.c

SRC_CLIENT_BONUS = client_bonus.c
SRC_SERVER_BONUS = server_bonus.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_HELP = $(HELP_FILE:.c=.o)

OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

all: client server

client: $(OBJ_CLIENT) $(OBJ_HELP)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(OBJ_HELP) -o $(NAME_CLIENT)

server: $(OBJ_SERVER) $(OBJ_HELP)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(OBJ_HELP) -o $(NAME_SERVER)

client_bonus: $(OBJ_CLIENT_BONUS) $(OBJ_HELP)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) $(OBJ_HELP) -o $(NAME_CLIENT_BONUS)

server_bonus: $(OBJ_SERVER_BONUS) $(OBJ_HELP)
	$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) $(OBJ_HELP) -o $(NAME_SERVER_BONUS)

bonus: client_bonus server_bonus

%.o: %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS) $(OBJ_HELP)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re: fclean all
