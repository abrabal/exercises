# Top-level Makefile for all K&R exercises

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -O2

# Find all main.c files
SOURCES := $(wildcard first_steps*/*/main.c)

# Map each main.c to its corresponding binary
BINARIES := $(SOURCES:%.c=%)

.PHONY: all clean

all: $(BINARIES)

# Rule to build each binary
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	@for bin in $(BINARIES); do \
		rm -f $$bin; \
	done