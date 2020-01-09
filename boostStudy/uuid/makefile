CC      = gcc
CXX     = g++
LINK    = g++
CFLAGS  = -g -Wall -O0
TARGET  = test 
SRCS    = $(wildcard *.cpp)
SRCS    += $(wildcard *.c)

#set your inc and lib  
INC = -I/root/thirdlib/boost_1_72_0
LIB = -lpthread -L/root/thirdlib/boost_1_72_0/stage/lib

CXX_OBJS    = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
C_OBJS  = $(patsubst %.c, %.o, $(wildcard *.c))

all:$(TARGET)

$(TARGET):$(CXX_OBJS) $(C_OBJS)
	$(LINK) $(CFLAGS) $(LIB) -o $@ $^
%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<
%.o:%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
.PHONY:clean
clean:
	rm -rf *.o $(TARGET) $(CXX_OBJS) $(C_OBJS)