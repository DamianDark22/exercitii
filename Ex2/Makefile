CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lrt
DEP = utils.h
FILE_S = server.c
FILE_C = client.c
TARGET_S = server
TARGET_C = client

ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

all: $(TARGET_S) $(TARGET_C)

$(TARGET_S): $(FILE_S) $(DEP)
	$(CC) $(CFLAGS) -o $(TARGET_S) $(FILE_S) $(LDFLAGS)

$(TARGET_C): $(FILE_C) $(DEP)
	$(CC) $(CFLAGS) -o $(TARGET_C) $(FILE_C) $(LDFLAGS)

.PHONY: run_client
run_client: $(TARGET_C)
	./$(TARGET_C) $(RUN_ARGS)

run_server: $(TARGET_S)
	./$(TARGET_S)

clean:
	rm -f  $(TARGET_C) $(TARGET_S)