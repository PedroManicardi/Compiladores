CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = analisador_lexico_sintatico
SRCS = main.c lexer.c asd.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)
