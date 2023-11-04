# CFLAGS = -Wall -pedantic -fno-stack-protector
CFLAGS = -Wall -pedantic
OBJS = main.o
PROG = aft
PROGT = advtest
PROGW = adv.wasm
CFLAGST = -Wall -pedantic -g
CXX = gcc
WCC=/opt/wasi-sdk/bin/clang --sysroot=/opt/wasi-sdk/share/wasi-sysroot -v -fuse-ld=lld

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

wasm:
	$(WCC) main.c -o $(PROGW)

# clean
clean:
	rm $(PROG) *.o save.aft

tclean:
	rm *.out