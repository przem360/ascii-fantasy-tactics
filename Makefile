CFLAGS = -Wall -pedantic
OBJS = main.o
PROG = aft
CXX = gcc

all: $(PROG)

# %.o: resources.h
# 	$(CXX) $(CFLAGS) -c -s $<

# linking
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG)

# clean
clean:
	rm $(PROG) *.o