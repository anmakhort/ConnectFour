#################################################################
# Makefile for 'Connect Four' GUI application
# Author: Anatolii MAKHORT
# e-mail: anmakhort@gmail.com
#################################################################

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -O3
#TARGET_VERBOSE = -D_VERBOSE
#DEFINES = -D_XOPEN_SOURCE
INCLUDES = -I./include -I/usr/include -I/usr/X11/include
LDFLAGS = -L/usr/lib -lXext -lX11 -lm -lpng
LIBS =

TARGET = ConnectFour

SOURCES = 	./src/main.c \
			./src/expose.c \
			./src/keyreleased.c

OBJECTS = $(SOURCES:.c=.o)

RM = rm -fr
MK = mkdir -p

.PHONY: all, run, clean, distclean, objclean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(LIBS)

%.o: %.c
	@$(CC) $(CFLAGS) $(DEFINES) $(TARGET_VERBOSE) $(DEBUG) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

distclean:
	@$(RM) $(TARGET)

objclean:
	@$(RM) $(OBJECTS)

clean: distclean objclean