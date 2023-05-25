srcdir=src
headers=$(srcdir)/hash.h $(srcdir)/xxhash.h

.PHONY: all clean
all: hash log cheatcodeforcer

hash: $(srcdir)/hash.o  $(srcdir)/xxhash.o
	$(CC) -o $@ $(srcdir)/hash.o $(srcdir)/xxhash.o

log: $(srcdir)/log.o  $(srcdir)/xxhash.o
	$(CC) -o $@ $(srcdir)/log.o $(srcdir)/xxhash.o

cheatcodeforcer: $(srcdir)/cheatcodeforcer.o $(srcdir)/xxhash.o
	$(CC) -o $@ $(srcdir)/cheatcodeforcer.o $(srcdir)/xxhash.o

$(srcdir)/hash.o: $(srcdir)/hash.c $(headers)
	$(CC) -c $(srcdir)/hash.c -o $@

$(srcdir)/log.o: $(srcdir)/log.c $(headers)
	$(CC) -c $(srcdir)/hash.c -o $@

$(srcdir)/cheatcodeforcer.o: $(srcdir)/xxhash.c $(srcdir)/xxhash.h
	$(CC) -c $(srcdir)/cheatcodeforcer.c -o $@

$(srcdir)/xxhash.o: $(srcdir)/xxhash.c
	$(CC) -c $(srcdir)/xxhash.c -o $@

$(srcdir)/xxhash.c $(srcdir)/xxhash.h: $(srcdir)/fetch-xxhash
	cd $(srcdir) && ./fetch-xxhash

distclean:
	rm -f hash log cheatcodeforcer $(srcdir)/hash.o $(srcdir)/log.o \
	$(srcdir)/cheatcodeforcer.o $(srcdir)/xxhash.o $(srcdir)/xxhash.c \
	$(srcdir)/xxhash.h

clean:
	rm -f hash log cheatcodeforcer $(srcdir)/hash.o $(srcdir)/log.o \
	$(srcdir)/cheatcodeforcer.o $(srcdir)/xxhash.o
