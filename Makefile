CC = c++
NAME = snake
SRC = main.cpp entity.cpp
CFLAGS = -I "C:\SDL\x86_64-w64-mingw32\include" -L "C:\SDL\x86_64-w64-mingw32\lib" -lSDL3

all: $(NAME)

$(NAME): $(SRC)
	$(CC) -o $(NAME) $(CFLAGS)

clean: 
	rm -rf $(NAME)

fclean: clean