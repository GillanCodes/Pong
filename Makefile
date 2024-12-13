build:
	gcc -o pong pong.c `sdl2-config --cflags --libs`

make clean:
	rm pong
