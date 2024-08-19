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

CFLAGS = -Wall -Wextra -Werror -g

OBJS = $(SRCS:.c=.o)

AR = ar -r 

ARNAME = fdf.a

PROG_NAME = fdf

LIBFT_PATH = ./src_files/my_libft/

all: $(ARNAME)
	clear
	@echo Making "\e[32m$(PROG_NAME)\e[0m"
	make -C $(LIBFT_PATH) all
	cc -g -o $(PROG_NAME) $(ARNAME) -Lminilibx-linux -lmlx -lX11 -lXext -lm -L$(LIBFT_PATH) -lft -g
	@echo "\e[32mDone.\e[0m"

$(ARNAME): $(OBJS)
	$(AR) $@ $(OBJS)

RM = rm -f

clean:
	@echo clean "\e[32m$(PROG_NAME)\e[0m"
	$(RM) $(OBJS)
	@echo clean "\e[32m$(LIBFT_PATH)\e[0m"
	make -C $(LIBFT_PATH) clean

fclean: clean
	@echo fclean "\e[32m$(LIBFT_PATH)\e[0m"
	make -C $(LIBFT_PATH) fclean
	$(RM) $(ARNAME)
	@if [ -e "$(PROG_NAME)" ]; then \
		echo "\e[32m$(PROG_NAME)\e[0m exist"; \
		$(RM) $(PROG_NAME); \
		echo "\e[32m$(PROG_NAME)\e[0m deleted"; \
	else \
		echo "\e[32m$(PROG_NAME)\e[0m not exist"; \
	fi

re: fclean
	make all

.PHONY: all clean fclean re
