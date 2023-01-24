include ./config.mk
CFLAGS = -O2
DEBUGFLAGS = -Wall -Wextra -Wpedantic
SRCFILES = $(wildcard ./src/*.c)
TESTFILES = $(wildcard ./test/*.c)
OBJFILES = $(SRCFILES:.c=.o)

compile: $(SRCFILES)
ifeq ($(IS_DYNAMIC), false)
	$(CC) $(DEBUGFLAGS) $(CFLAGS) -c $(SRCFILES) -o $(OBJFILES)
	$(AR) rcs libcute.a $(OBJFILES)
else ifeq ($(IS_DYNAMIC), true)
	$(CC) $(DEBUGFLAGS) $(CFLAGS) -fPIC -c $(SRCFILES) -o $(OBJFILES)
	$(CC) $(CFLAGS) -shared -o libcute.so $(OBJFILES)
endif

test: compile
ifeq ($(IS_DYNAMIC), true)
	@echo "Be sure to set \$LD_LIBRARY_PATH to this current directory"
endif
	$(CC) $(CFLAGS) -c $(TESTFILES) -o $(TESTFILES:.c=.o)
	$(CC) $(CFLAGS) -o main $(TESTFILES:.c=.o) -L. -lcute
	./main

clean:
	rm $(OBJFILES) $(TESTFILES:.c=.o) libcute.a libcute.so main
