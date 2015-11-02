
TARGET = ugui.o
SOURCES = main.c source/window.c source/layer.c source/canvas_layer.c source/graphics.c source/bmp.c source/ugui.c
CFLAGS = -std=c11 -g
IFLAGS = -I./include

all: $(SOURCES)
	gcc $(CFLAGS) $(SOURCES) $(IFLAGS) -o $(TARGET)