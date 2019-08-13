CC = g++
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
LIBS = -lboost_unit_test_framework

test: $(OBJS)
	$(CC) -o test $(OBJS)

%.d: %.cpp
	@set -e; rm -f $@; \
    $(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
    rm -f $@.$$$$
    
sinclude $(SRCS:.cpp=.d)

.PHONY: clean
clean:
	-rm test $(OBJS) *.d
