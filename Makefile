print-%: ; @echo $($*)

CC = gcc
LD = gcc

# library paths
PATH_LIB = lib
PATH_SDL = $(PATH_LIB)/SDL

INCFLAGS = -Isrc
CCFLAGS = -std=c2x
CCFLAGS += -O2
CCFLAGS += -g
CCFLAGS += -fbracket-depth=1024
CCFLAGS += -fmacro-backtrace-limit=0
CCFLAGS += -Wall
CCFLAGS += -Wextra
CCFLAGS += -Wpedantic
CCFLAGS += -Wfloat-equal
CCFLAGS += -Wstrict-aliasing
CCFLAGS += -Wswitch-default
CCFLAGS += -Wformat=2
CCFLAGS += -Wno-newline-eof
CCFLAGS += -Wno-unused-parameter
CCFLAGS += -Wno-strict-prototypes
CCFLAGS += -Wno-fixed-enum-extension
CCFLAGS += -Wno-int-to-void-pointer-cast
CCFLAGS += -Wno-gnu-statement-expression
CCFLAGS += -Wno-gnu-compound-literal-initializer
CCFLAGS += -Wno-gnu-zero-variadic-macro-arguments
CCFLAGS += -Wno-gnu-empty-struct
CCFLAGS += -Wno-gnu-auto-type
CCFLAGS += -Wno-gnu-empty-initializer
CCFLAGS += -Wno-gnu-pointer-arith
CCFLAGS += -Wno-c99-extensions
CCFLAGS += -Wno-c11-extensions

LDFLAGS = -lm

BIN = bin
SRC_DIR = src
SRC_DIRS = $(shell find $(SRC_DIR) -type d)
SRC = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJ = $(SRC:%.c=$(BIN)/%.o)
DEP = $(SRC:%.c=$(BIN)/%.d)
OUT = $(BIN)/mapped_engine

-include $(DEP)

UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
  CC = /usr/bin/clang
  LD = /usr/bin/clang
  INCFLAGS += -I$(PATH_SDL)/include
  LDFLAGS += $(shell $(BIN)/sdl/sdl2-config --prefix=$(BIN) --static-libs)
else ifeq ($(UNAME),Linux)
  LDFLAGS += -lSDL2
endif

$(BIN):
	mkdir -p $@

dirs: $(BIN)
	rsync -a --include '*/' --exclude '*' "$(SRC_DIR)" "$(BIN)"

lib-sdl:
	mkdir -p $(BIN)/sdl
	cmake -S $(PATH_SDL) -B $(BIN)/sdl
	cd $(BIN)/sdl && make -j 10
	chmod +x $(BIN)/sdl/sdl2-config
	mkdir -p $(BIN)/lib
	cp $(BIN)/sdl/libSDL2.a $(BIN)/lib

libs: lib-sdl

$(OBJ): $(BIN)/%.o: %.c
	$(CC) -o $@ -MMD -c $(CCFLAGS) $(INCFLAGS) $<

$(OUT): $(OBJ)
	$(LD) -o $@ $^ $(LDFLAGS)

engine: dirs $(OUT)

all: dirs engine

clean:
	rm -rf $(BIN)
