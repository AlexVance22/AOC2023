BIN = aoc23
EXT = c
STD =
CC = gcc
LD = gcc

SDIR = src
ODIR = obj

CFLAGS = -Wall $(STD) -DDEBUG
LFLAGS = -Wall $(STD)

DEPS = $(wildcard $(SDIR)/*.h)
SRCS = $(wildcard $(SDIR)/*.$(EXT))
OBJS = $(patsubst $(SDIR)/%.$(EXT), $(ODIR)/%.o, $(SRCS))


$(BIN): $(OBJS)
	@echo "  linking:" $@
	@$(LD) -o $@ $^ $(LFLAGS)

$(BIN)-r: $(OBJS)
	@echo "  linking:" $@
	@$(LD) -o $@ $^ $(LFLAGS)

$(ODIR)/%.o: $(SDIR)/%.$(EXT) $(DEPS)
	@echo "compiling:" $<
	@$(CC) -o $@ -c $< $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(OBJS)
	rm -f $(BIN)
	rm -f $(BIN)-r


.PHONY: all

all: $(BIN)


.PHONY: release

release: CFLAGS = -Wal $(STD) -O2 -DNDEBUG
release: LFLAGS = -Wal $(STD) -O2
release: clean
release: $(BIN)-r


.PHONY: run

run: $(BIN)
	@echo "  running: ----------"
	@./$(BIN)

