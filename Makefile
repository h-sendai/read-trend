PROG = read-trend
CFLAGS += -g -O2 -Wall
CFLAGS += -std=gnu17
# CFLAGS += -pthread
# LDLIBS += -L/usr/local/lib -lmylib
# LDLIBS += -lrt
# LDFLAGS += -pthread

all: $(PROG)
OBJS += $(PROG).o
OBJS += my_signal.o
OBJS += my_socket.o
OBJS += get_num.o
OBJS += set_timer.o
OBJS += set_cpu.o
OBJS += logUtil.o
OBJS += readn.o

$(PROG): $(OBJS)

clean:
	rm -f *.o $(PROG)
