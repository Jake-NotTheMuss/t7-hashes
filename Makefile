srcdir=src
headers=$(srcdir)/hash.h

.PHONY: all clean
all: hash log

hash: $(srcdir)/hash.o
	$(CC) -o $@ $<

log: $(srcdir)/log.o
	$(CC) -o $@ $<

$(srcdir)/hash.o: $(srcdir)/hash.c $(headers)
	$(CC) -c $< -o $@

$(srcdir)/log.o: $(srcdir)/log.c $(headers)
	$(CC) -c $< -o $@

clean:
	rm -f hash log $(srcdir)/hash.o $(srcdir)/log.o
