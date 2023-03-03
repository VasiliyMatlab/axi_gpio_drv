CC = $(PREFIX)gcc
AR = $(CC)-ar

LIBPATH = lib
BUILDPATH = build
SRCPATH = src

all:
	mkdir -p $(LIBPATH)
	mkdir -p $(BUILDPATH)
	$(CC) -Wall -Wextra -c $(SRCPATH)/axi_gpio.c -o $(BUILDPATH)/axi_gpio.o
	$(AR) crf $(LIBPATH)/libaxi_gpio.a $(BUILDPATH)/axi_gpio.o

clean:
	rm -rf $(LIBPATH)
	rm -rf $(BUILDPATH)
