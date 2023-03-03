CC := $(PREFIX)gcc
AR := $(CC)-ar

LIBPATH   := lib
BUILDPATH := build
INCPATH   := src
SRCPATH   := src

SRCS := $(wildcard $(SRCPATH)/*.c)
INCS := $(wildcard $(SRCPATH)/*.h)
OBJS := $(patsubst $(SRCPATH)/%.c, $(BUILDPATH)/%.o, $(SRCS))
LIB  := $(LIBPATH)/libaxi_gpio.a

CFLAGS  := -O2 -Wall -Wextra -std=gnu99
ARFLAGS := crf

all: start $(LIB)
	$(info Building complete)

start:
	$(info Start building)
	mkdir -p $(LIBPATH)
	mkdir -p $(BUILDPATH)

$(LIB): $(OBJS) $(INCS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

$(BUILDPATH)/%.o:$(SRCPATH)/%.c
	$(CC) $(CFLAGS) -c $< -I$(INCPATH) -o $@

clean:
	rm -rf $(BUILDPATH) $(LIBPATH)

.PHONY: all start clean
