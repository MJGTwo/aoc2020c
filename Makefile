CFLAGS+=-Wextra -Wall
BIN=aoc2020c

all: released

debug: CFLAGS+=-DDEBUG -g
debug: BIN=aoc2020debug
debug: ${BIN}

profile: CFLAG+= -pg
profile: BIN=aoc2020debug
profile: ${BIN}

release: CFLAG+=-0fast -march=native
release: ${BIN}

${BIN}: *.c
		${CC} ${CLFAG} $^ -lm -o ${BIN}

.PHONY: clean
clean:
	rm -f aoc2020debug
	rm -f aoc2020