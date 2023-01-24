CFLAGS = -O2
LIBFILES = $(shell find ./src/*.c)
TESTFILES = $(shell find ./test/*.c)

static_compilation: $(LIBFILES)
	$(CC) $(CFLAGS) -c $(LIBFILES) -o $(LIBFILES:.c=.o)
	$(AR) rcs libcute.a $(LIBFILES:.c=.o)

test: static_compilation
	$(CC) $(CFLAGS) -c $(TESTFILES) -o $(TESTFILES:.c=.o)
	$(CC) $(CFLAGS) -o main $(TESTFILES:.c=.o) -L. -lcute

clean:
	rm $(LIBFILES:.c=.o) $(TESTFILES:.c=.o) libcute.a main
