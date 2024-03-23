# CFLAGS = -Wall -pedantic -fno-stack-protector
CFLAGS = -Wall -pedantic
# CFLAGS= -g -O0
OBJS = helpers.o converters.o asciibattle.o textadventure.o main.o
PROG = aft
PROGT = advtest
PROGW = adv.wasm
# CFLAGST = -Wall -pedantic -g
CXX = gcc
WCC=/opt/wasi-sdk/bin/clang --sysroot=/opt/wasi-sdk/share/wasi-sysroot
# CXX = $(WCC)
# CFLAGS = -v -fuse-ld=lld

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(PROG)


runtest:
	# gdb aft --command=battle.gdb
	gdb aft

wasm:
	$(WCC) main.c -o $(PROGW)






main.o: asciibattle.h textadventure.h main.c
	$(CXX) $(CFLAGS) -c main.c -o main.o # Main

asciibattle.o: settings.h colors.h resources.h asciibattle.h asciibattle.c
	$(CXX) $(CFLAGS) -c asciibattle.c -o asciibattle.o # Ascii Battle

textadventure.o: settings.h locations.h colors.h textadventure.h asciibattle.h textadventure.c
	$(CXX) $(CFLAGS) -c textadventure.c -o textadventure.o # Text Adventure

converters.o: converters.h converters.c
	$(CXX) $(CFLAGS) -c converters.c -o converters.o # Converters

helpers.o: settings.h helpers.h helpers.c
	$(CXX) $(CFLAGS) -c helpers.c -o helpers.o # Helpers

clean:
	rm -f $(PROG) *.o save.aft *.out gdb.output