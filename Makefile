NAME	= server

CC	= gcc

RM	= rm -f

SRCS	= ./src/main.c \
		./src/str_tools.c \
		./src/socket.c \
		./src/client.c \
		./src/ftp.c \
		./src/passive.c \
		./src/cmds/user.c \
		./src/cmds/pass.c \
		./src/cmds/cwd.c \
		./src/cmds/cdup.c \
		./src/cmds/quit.c \
		./src/cmds/dele.c \
		./src/cmds/pwd.c \
		./src/cmds/pasv.c \
		./src/cmds/port.c \
		./src/cmds/help.c \
		./src/cmds/noop.c \
		./src/cmds/retr.c \
		./src/cmds/stor.c \
		./src/cmds/list.c \
		./src/cmds/auth.c \
		./src/cmds/type.c \

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I 
CFLAGS += -W -Wall -Wextra -g

LDFLAGS += -pthread

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
