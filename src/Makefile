CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = analisador_lexico
SRCS = main.c lexer.c 
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)
