CFLAGS = -Wall -pedantic
OBJS = main.o
PROG = aft
# PROGT = aftest
CFLAGST = -Wall -pedantic -g
CXX = gcc

all: $(PROG) $(PROGT)

# %.o: resources.h
# 	$(CXX) $(CFLAGS) -c -s $<

# linking
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG)

# $(PROGT): $(OBJS)
# 	$(CXX) -g main.c 

# clean
clean:
	rm $(PROG) *.o

tclean:
	rm *.out