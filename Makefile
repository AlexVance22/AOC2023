BIN = aoc23

SDIR = src
ODIR = obj

CFLAGS = -Wall -DDEBUG
LFLAGS = -Wall

DEPS = $(wildcard $(SDIR)/*.h)
SRCS = $(wildcard $(SDIR)/*.c)
OBJS = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRCS))


$(BIN): $(OBJS)
	@echo "  linking:" $@
	@gcc -o $@ $^ $(LFLAGS)

$(BIN)-r: $(OBJS)
	@echo "  linking:" $@
	@gcc -o $@ $^ $(LFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@echo "compiling:" $<
	@gcc -o $@ -c $< $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(OBJS)
	rm -f $(BIN)
	rm -f $(BIN)-r


.PHONY: release

release: CFLAGS = -Wall -O2 -DNDEBUG
release: LFLAGS = -Wall -O2
release: clean
release: $(BIN)-r


.PHONY: run

run: $(BIN)
	@echo "  running: ----------"
	@./$(BIN)

