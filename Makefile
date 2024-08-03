# %.o: %.c
#	 $(CC) $(CFLAGS) -c $? -o $@
# is replaced by
# "OBJS = $(SRCS:.c=.o)"

SRCS = \
	01_main.c \
	02_get_parsed_data.c \
	03_splits_to_points.c \
	04_iso_prjc.c \
	05_adjust_scale.c \
	06_draw_line.c \
	07_put_pixel.c \
	99_free_data.c \
	99_my_mlx_pixel_put.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

AR = ar -r 

NAME = libftprintf.a

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
