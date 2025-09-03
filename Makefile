CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror -O2
AR := ar

SRC := src/util.c
OBJ := $(SRC:.c=.o)

TESTS := tests/test_util
TEST_OBJS := $(TESTS:=.o)

.PHONY: all clean test format format-check tidy

all: build

build: libutil.a app

libutil.a: $(OBJ)
	$(AR) rcs $@ $^

app: src/main.o libutil.a
	$(CC) $(CFLAGS) -o $@ src/main.o -L. -lutil

tests/%: tests/%.o libutil.a
	$(CC) $(CFLAGS) -o $@ $< -L. -lutil

test: $(TESTS)
	@set -e; for t in $(TESTS); do echo "RUN $$t"; ./$$t; done

format:
	@clang-format -i src/*.c src/*.h tests/*.c

format-check:
	@clang-format -n --Werror src/*.c src/*.h tests/*.c

tidy:
	@clang-tidy src/*.c -- -std=c11

clean:
	rm -f $(OBJ) $(TEST_OBJS) src/main.o app libutil.a $(TESTS)
