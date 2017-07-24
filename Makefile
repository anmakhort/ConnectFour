#################################################################
# Makefile for 'Connect Four' GUI application
# Author: Anatolii MAKHORT
# e-mail: anmakhort@gmail.com
#################################################################

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -O3
INCLUDES = -I./include -I/usr/include -I/usr/X11/include
LDFLAGS = -L/usr/lib -lXext -lX11 -lm -lpng
LIBS =

TARGET = ConnectFour

SOURCES = 	./src/main.c \
			./src/expose.c \
			./src/keyreleased.c \
			./src/update.c \
			./src/cleanup.c \
			./src/color.c \
			./src/createimg.c \
			./src/drawgame.c \
			./src/animate.c \
			./src/newgame.c \
			./src/mousekey.c \
			./src/getGC.c \
			./src/getwinner.c

OBJECTS = $(SOURCES:.c=.o)

RM = rm -fr
MK = mkdir -p

.PHONY: all, run, memtest, clean, distclean, objclean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(LIBS)

%.o: %.c
	@$(CC) $(CFLAGS) $(DEFINES) $(TARGET_VERBOSE) $(DEBUG) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

memtest: all
	@G_SLICE=always-malloc G_DEBUG=gc-friendly \
	valgrind -v --tool=memcheck --leak-check=full --leak-check-heuristics=all \
	--show-mismatched-frees=yes --expensive-definedness-checks=yes --show-leak-kinds=all ./$(TARGET)

distclean:
	@$(RM) $(TARGET)

objclean:
	@$(RM) $(OBJECTS)

clean: distclean objclean