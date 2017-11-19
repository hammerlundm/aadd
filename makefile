EXEC = aadd
CFLAGS = -Wall -Iinclude
CC = gcc $(CFLAGS)
LIBS = -lmpdclient
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

all: debug

debug: CFLAGS += -DDEBUG -g
debug: release

release: $(OBJECTS)
	$(CC) $^ $(LIBS) -o $(EXEC)

%.o: src/%.c
	$(CC) -c -MMD -MP $< -o $@

clean:
	rm -f $(DEPENDS) $(OBJECTS) $(EXEC)

-include $(DEPENDS)

