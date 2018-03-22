all: test

test: main.c
	$(CC) $< -lXext -lX11 -o test
