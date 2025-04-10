##
## EPITECH PROJECT, 2025
## pool tek 2
## File description:
## Makefile
##

CORE				=	src/core/ArcadeCore.cpp

NCURSES 			=	src/graphic/Ncurses.cpp

SDL 				=	src/graphic/LibSdl.cpp

SFML				= 	src/graphic/Sfml.cpp

MENU				=	src/games/Menu.cpp

MINESWEEPER			=	src/games/Minesweeper.cpp

SNAKE				=	src/games/Snake.cpp


MAIN				=	main.cpp

LIB_PATH 			=	./lib/

CXXFLAGS 			= 	-Wall -Wextra -std=c++20 	\
						-iquote include 				\
						-iquote include/data 		\
						-iquote include/interfaces 	\
						-iquote src 					\
						-iquote src/error 			\
						-iquote src/graphic 			\


CORE_OBJ			=	$(CORE:.cpp=.o)

NCURSES_FLAGS		= 	-lncurses

SDL_FLAGS 			=	-lSDL2 -lSDL2_image -lSDL2_ttf

SFML_FLAGS 			=	-lsfml-graphics -lsfml-window -lsfml-system

DYNAMIC_FLAGS 		=	-fPIC -shared

NAME				=	arcade

NCURSES_NAME		=	arcade_ncurses.so

SDL_NAME			=	arcade_sdl2.so

SFML_NAME			=	arcade_sfml.so

MENU_NAME 			=	arcade_menu.so

MINESWEEPER_NAME	=	arcade_minesweeper.so

SNAKE_NAME			=	arcade_snake.so

TEST_FLAG			=	--verbose -lcriterion

CXX					= 	g++

MV 					=	mv

core: $(NAME)

games: $(MENU_NAME) $(MINESWEEPER_NAME) $(SNAKE_NAME)

graphicals: $(NCURSES_NAME) $(SDL_NAME) $(SFML_NAME)

all: $(NAME) $(NCURSES_NAME) $(SDL_NAME) $(SFML_NAME) $(MENU_NAME) $(MINESWEEPER_NAME) $(SNAKE_NAME)

$(MENU_NAME):
	$(CXX) $(DYNAMIC_FLAGS) $(CXXFLAGS) $(MENU) -o $(MENU_NAME)
	$(MV) $(MENU_NAME) $(LIB_PATH)

$(MINESWEEPER_NAME):
	$(CXX) $(DYNAMIC_FLAGS) $(CXXFLAGS) $(MINESWEEPER) -o $(MINESWEEPER_NAME)
	$(MV) $(MINESWEEPER_NAME) $(LIB_PATH)

$(SNAKE_NAME):
	$(CXX) $(DYNAMIC_FLAGS) $(CXXFLAGS) $(SNAKE) -o $(SNAKE_NAME)
	$(MV) $(SNAKE_NAME) $(LIB_PATH)

$(NCURSES_NAME):
	$(CXX) $(NCURSES_FLAGS) $(CXXFLAGS) $(DYNAMIC_FLAGS) $(NCURSES) -o $(NCURSES_NAME)
	$(MV) $(NCURSES_NAME) $(LIB_PATH)

$(SDL_NAME):
	$(CXX) $(DYNAMIC_FLAGS) $(CXXFLAGS) $(SDL_FLAGS) $(SDL) -o $(SDL_NAME)
	$(MV) $(SDL_NAME) $(LIB_PATH)

$(SFML_NAME):
	$(CXX) $(DYNAMIC_FLAGS) $(CXXFLAGS) $(SFML_FLAGS) $(SFML) -o $(SFML_NAME)
	$(MV) $(SFML_NAME) $(LIB_PATH)

$(NAME): $(CORE_OBJ)
	$(CXX) -o $(NAME) $(CXXFLAGS) $(CORE_OBJ) $(MAIN)

tests_run: $(CORE_OBJ)
	$(CXX) $(CORE) -o tests $(TEST_FLAG) test.cpp

clean:
	$(RM) $(CORE_OBJ)
	$(RM) $(GRAPHIC_OBJ)

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(LIB_PATH)$(NCURSES_NAME)
	$(RM) $(LIB_PATH)$(MENU_NAME)
	$(RM) $(LIB_PATH)$(SDL_NAME)
	$(RM) $(LIB_PATH)$(MINESWEEPER_NAME)
	$(RM) $(LIB_PATH)$(SNAKE_NAME)
	$(RM) $(LIB_PATH)$(SFML_NAME)
	$(RM) tests

re:	fclean all

.PHONY: all clean fclean re tests_run
