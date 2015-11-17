
TARGET = ugui.o
SOURCES = example/source/main.c example/source/line_window.c example/source/circle_window.c example/source/layer_window.c
LIBS = library/source/window.c library/source/layer.c library/source/graphics.c library/source/bmp.c library/source/ugui.c
FONTS = library/source/fonts/robotomono_regular_16.c library/source/fonts/robotomono_regular_18.c
CFLAGS = -std=c11 -g
IFLAGS = -I./library/include -I./example/include

all: $(SOURCES)
	gcc $(CFLAGS) $(SOURCES) $(LIBS) $(FONTS) $(IFLAGS) -o $(TARGET)