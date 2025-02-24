CFLAGS = -Wall -pedantic
OBJS = helpers.o convert.o abattle.o txtadv.o main.o
PROG = aft.exe
PROGT = advtest
CXX = gcc
SYS = -DSYSTEM='"DOS"'
RM = del

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(PROG)


runtest:
	# gdb aft --command=battle.gdb
	gdb aft


run: $(PROG)
	./$(PROG)




main.o: abattle.h txtadv.h main.c
	$(CXX) $(CFLAGS) -c main.c -o main.o $(SYS)

abattle.o: settings.h colors.h res.h abattle.h abattle.c
	$(CXX) $(CFLAGS) -c abattle.c -o abattle.o

txtadv.o: settings.h locs.h colors.h txtadv.h abattle.h txtadv.c
	$(CXX) $(CFLAGS) -c txtadv.c -o txtadv.o

convert.o: convert.h convert.c
	$(CXX) $(CFLAGS) -c convert.c -o convert.o

helpers.o: settings.h helpers.h helpers.c
	$(CXX) $(CFLAGS) -c helpers.c -o helpers.o $(SYS)

clean:
	$(RM) $(PROG)
	$(RM) *.o
	$(RM) save.aft
	$(RM) *.out
	$(RM) gdb.output
	$(RM) *.log