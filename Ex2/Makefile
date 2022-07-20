CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lrt
DEP = utils.h
FILES = main.c
OBJFILES = main.o
TARGET = main

ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

.PHONY: run
run: $(TARGET)
	./$(TARGET) $(RUN_ARGS)

clean:
	rm -f $(OBJFILES) $(TARGET)