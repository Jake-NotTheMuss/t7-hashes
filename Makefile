
common_src:=

hasher_src:=src/hash.c $(common_src)
logger_src:=src/log.c $(common_src)

hasher_obj:=$(hasher_src:%.c=%.o)
logger_obj:=$(logger_src:%.c=%.o)

objects:=$(hasher_obj) $(logger_obj)

deps:=$(hasher_src:%.c=%.d) $(logger_src:%.c=%.d)

.PHONY: all clean

all: hash log

hash: $(hasher_obj)
	$(CC) -o $@ $^

log: $(logger_obj)
	$(CC) -o $@ $^

$(objects): %.o: %.c %.d
	$(CC) -MT $@ -MMD -MP -MF $*.d -c $< -o $@

$(deps):

clean:
	rm -f hash log $(objects) $(deps)

include $(wildcard $(deps))
