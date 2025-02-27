CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = signal_test

# Server and client object files
OBJ_SERVER = server.o
OBJ_CLIENT = client.o

all: $(NAME)

$(NAME): $(OBJ_SERVER) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_SERVER) $(OBJ_CLIENT)

server.o: server.c header.h
	$(CC) $(CFLAGS) -c server.c

client.o: client.c header.h
	$(CC) $(CFLAGS) -c client.c

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	rm -f $(NAME)

re: fclean all
