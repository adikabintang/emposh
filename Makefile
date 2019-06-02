BIN=emposh.out
IDIR=./include
SRCDIR=./src
CC=clang
CFLAGS=-I$(IDIR)
ODIR=obj

INCLUDES = $(wildcard include/*.h)
DEPS = $(patsubt %,$(IDIR)/%,$(INCLUDES))

SRC	= $(wildcard src/*.c)
_OBJ = $(patsubst src/%.c, %.o, $(SRC))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	@echo "Compiled "$<" successfully!"

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean memcheck

memcheck:
	valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes \
	./$(BIN)

clean:
	rm -f $(ODIR)/*.o *.out