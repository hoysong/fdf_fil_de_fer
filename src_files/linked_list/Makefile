SRCS = \
	doubly_lkdlist.c \
	doubly_lkdlist_destroy.c \
	singly_lkdlist.c \

CC = cc

CFLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

AR = ar -U -r -u -s 

NAME = liblkdlist.a

$(NAME): $(OBJS)
	$(AR) $@ $(OBJS)

all: $(NAME)

RM = rm -f

clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
