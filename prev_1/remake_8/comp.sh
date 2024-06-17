comp() {
		cc *.c -Lminilibx-linux -lmlx -Lmy_libft -lft -lX11 -lXext
		run_valg
}

run_valg() {
		valgrind ./a.out test
}

comp
