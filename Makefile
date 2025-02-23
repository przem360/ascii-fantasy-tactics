CFLAGS = -Wall -pedantic
# CFLAGS= -g -O0
OBJS = helpers.o convert.o abattle.o txtadv.o main.o
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


run: $(PROG)
	./$(PROG)




main.o: abattle.h txtadv.h main.c
	$(CXX) $(CFLAGS) -c main.c -o main.o # Main

abattle.o: settings.h colors.h res.h abattle.h abattle.c
	$(CXX) $(CFLAGS) -c abattle.c -o abattle.o # Ascii Battle

txtadv.o: settings.h locs.h colors.h txtadv.h abattle.h txtadv.c
	$(CXX) $(CFLAGS) -c txtadv.c -o txtadv.o # Text Adventure

convert.o: convert.h convert.c
	$(CXX) $(CFLAGS) -c convert.c -o convert.o # Converters

helpers.o: settings.h helpers.h helpers.c
	$(CXX) $(CFLAGS) -c helpers.c -o helpers.o # Helpers

clean:
	rm -f $(PROG) *.o save.aft *.out gdb.output *.log
