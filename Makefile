SRCS = \
	01_main.c             \
	02_get_parsed_data.c  \
	03_splits_to_points.c \
	04_iso_prjc.c         \
	05_adjust_scale.c     \
	06_draw_line.c        \
	07_put_pixel.c        \
	08_put_pixel.c        \
	09_free_data.c        \
	99_my_mlx_pixel_put.c \

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

AR = ar -r 

NAME = fdf.a

LIBFT_PATH = ./src_files/my_libft/

$(NAME): $(OBJS)
	$(AR) $@ $(OBJS)

all: $(NAME)
	make -C $(LIBFT_PATH) all
	cc -o fdf $(NAME) -Lminilibx-linux -lmlx -Lsrc_files/my_libft -lft -Lsrc_files/linked_list -llkdlist -lX11 -lXext -lm -g
RM = rm -f

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean
	rm fdf

re: fclean
	make all

.PHONY: all clean fclean re
