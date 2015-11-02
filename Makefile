
TARGET = ugui.o
SOURCES = example/main.c library/source/window.c library/source/layer.c library/source/graphics.c library/source/bmp.c library/source/ugui.c
CFLAGS = -std=c11 -g
IFLAGS = -I./library/include

all: $(SOURCES)
	gcc $(CFLAGS) $(SOURCES) $(IFLAGS) -o $(TARGET)