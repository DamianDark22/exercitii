# Protocoale de comunicatii:
# Laborator 8: Multiplexare
# Makefile

CFLAGS = -Wall -g

ifeq (run_client,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

# Portul pe care asculta serverul (de completat)
PORT = 4242

# Adresa IP a serverului (de completat)
IP_SERVER = 127.0.0.1

all: server client

# Compileaza server.c
server: server.c

# Compileaza client.c
client: client.c

.PHONY: clean run_server run_client

# Ruleaza serverul
run_server:
	./server ${PORT}

# Ruleaza clientul
.PHONY: run_client
run_client:
	./client ${IP_SERVER} ${PORT} $(RUN_ARGS)

clean:
	rm -f server client
