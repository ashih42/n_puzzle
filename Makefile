# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashih <ashih@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/06 15:12:23 by ashih             #+#    #+#              #
#    Updated: 2018/09/11 20:31:45 by ashih            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++

TARGET = npuzzle

SDL2_LOC := $(shell brew --prefix sdl2)
SDL2_INC := $(SDL2_LOC)/include/SDL2/
SDL2_LINK := -L $(SDL2_LOC)/lib/ -lSDL2

SDL2_IMAGE_LOC := $(shell brew --prefix sdl2_image)
SDL2_IMAGE_INC := $(SDL2_IMAGE_LOC)/include/SDL2/
SDL2_IMAGE_LINK := -L $(SDL2_IMAGE_LOC)/lib/ -lSDL2_image

SDL2_TTF_LOC := $(shell brew --prefix sdl2_ttf)
SDL2_TTF_INC := $(SDL2_TTF_LOC)/include/SDL2/
SDL2_TTF_LINK := -L $(SDL2_TTF_LOC)/lib/ -lSDL2_ttf

CFLAGS = -Wall -Werror -Wextra -Wfatal-errors
HEADERS = -I $(INCLUDES) -I $(SDL2_INC) -I $(SDL2_IMAGE_INC) -I $(SDL2_TTF_INC)

INCLUDES = includes/

SRCSDIR = srcs/
SRCS = main.cpp \
NPuzzle.cpp \
Board.cpp \
Piece.cpp \
Visualizer.cpp \
VisualizerInitializationException.cpp \
AMove.cpp \
MoveLeft.cpp \
MoveRight.cpp \
MoveDown.cpp \
MoveUp.cpp \
Lexer.cpp \
Parser.cpp \
ParserException.cpp \
Solver.cpp \
MyComparator.cpp

OBJDIR = objs/
OBJS = $(addprefix $(OBJDIR), $(SRCS:.cpp=.o))

all: sdl2 sdl2_image sdl2_ttf $(TARGET)

sdl2:
	@echo "\x1b[1mInstalling SDL2 library...\x1b[0m"
	@HOMEBREW_NO_AUTO_UPDATE=1 brew install sdl2
	@echo

sdl2_image:
	@echo "\x1b[1mInstalling SDL2 Image library...\x1b[0m"
	@HOMEBREW_NO_AUTO_UPDATE=1 brew install sdl2_image
	@echo

sdl2_ttf:
	@echo "\x1b[1mInstalling SDL2 TTF library...\x1b[0m"
	@HOMEBREW_NO_AUTO_UPDATE=1 brew install sdl2_ttf
	@echo

$(OBJDIR)%.o: $(SRCSDIR)%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $(HEADERS) $< -o $@

$(TARGET): $(OBJS)
	@echo "\x1b[1mBuilding $(TARGET)...\x1b[0m"
	$(CC) -o $(TARGET) $(OBJS) -lpthread $(SDL2_LINK) $(SDL2_IMAGE_LINK) $(SDL2_TTF_LINK)
	@echo "\x1b[1mBuild finished!!\x1b[0m"

clean:
	@echo "\x1b[1mCleaning...\x1b[0m"
	/bin/rm -rf $(OBJDIR)
	@echo

fclean: clean
	@echo "\x1b[1mFcleaning...\x1b[0m"
	/bin/rm -f $(TARGET)
	@echo

re: fclean all

.PHONY: all clean fclean re sdl2 sdl2_image sdl2_ttf
