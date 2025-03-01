CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME_S = server
NAME_C = client
BONUS_NAME_S = server_bonus
BONUS_NAME_C = client_bonus

COMM_SRC =includes/ft_atoi.c includes/ft_strchr.c put_str/put_str.c put_str/ft_putadr.c put_str/ft_putchar.c put_str/ft_putnbrbase.c put_str/ft_putnbrbaseunsigned.c put_str/ft_putnbr.c put_str/ft_putstr.c put_str/ft_strlen.c
SRC_S = server.c 
SRC_C = client.c

C_BONUS_SRC = clinet_bonus.c
S_BONUS_SRC = server_bonus.c

COMM_OBJ = $(COMM_SRC:.c=.o)
OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)
BONUS_OBJ_S = $(S_BONUS_SRC:.c=.o)
BONUS_OBJ_C = $(C_BONUS_SRC:.c=.o)


%.o: %.c minitalk.h
	@ $(CC) $(FLAGS) -o $@ -c $<
	
all: client server

server: $(OBJ_S) $(COMM_OBJ)
	@ $(CC) $(FLAGS) $(COMM_OBJ) $(OBJ_S) -o $(NAME_S)

client: $(OBJ_C) $(COMM_OBJ)
	@ $(CC) $(FLAGS) $(COMM_OBJ) $(OBJ_C) -o $(NAME_C)

bonus : client_bonus server_bonus

client_bonus: $(BONUS_OBJ_C) $(COMM_OBJ)
	@ $(CC) $(FLAGS) $(COMM_OBJ) $(BONUS_OBJ_C) -o $(BONUS_NAME_C)
server_bonus: $(BONUS_OBJ_S) $(COMM_OBJ)
	@ $(CC) $(FLAGS) $(COMM_OBJ) $(BONUS_OBJ_S) -o $(BONUS_NAME_S)

clean:
	@ $(RM) $(OBJ_S) $(OBJ_C)  $(COMM_OBJ) $(BONUS_OBJ_C) $(BONUS_OBJ_S) 

fclean: clean
	@ $(RM) $(NAME_S) $(NAME_C) $(BONUS_NAME_S) $(BONUS_NAME_C)

re: clean all

.PHONY: clean
