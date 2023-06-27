CFLAGS = -Wall -pedantic
OBJS = main.o
PROG = adv
PROGT = advtest
CFLAGST = -Wall -pedantic -g
CXX = gcc

all: $(PROG)

# %.o: resources.h
# 	$(CXX) $(CFLAGS) -c -s $<

# linking
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG)

# $(PROGT): $(OBJS)
# 	$(CXX) -g main.c 

# testing
test: $(PROGT)

$(PROGT): $(OBJS)
	$(CXX) -g $(OBJS)

runtest:
	gdb a.out

# clean
clean:
	rm $(PROG) *.o

tclean:
	rm *.out