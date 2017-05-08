EXEC_NAME = file-poll
SRCS = file_poll.c
CFLAGS = -O2 -Wall
OBJS = $(SRCS:.c=.o)

all: $(EXEC_NAME)

OBJS: $(SRCS:.c=.o)
	$(CC) $(CFLAGS) -c $<

$(EXEC_NAME): $(OBJS)
	$(CC) -o $(EXEC_NAME) ${OBJS} $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o $(EXEC_NAME)

