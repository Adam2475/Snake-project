CC = c++
NAME = snake
SRC = main.cpp entity.cpp player/player.cpp player/movement.cpp \
		collectables/collectable.cpp

CFLAGS = -I "C:\SDL\x86_64-w64-mingw32\include" -L "C:\SDL\x86_64-w64-mingw32\lib" -lSDL3

all: $(NAME)

$(NAME):
	$(CC) -o $(NAME) $(SRC) $(CFLAGS)

clean: 
	rm -f $(NAME)

fclean: clean