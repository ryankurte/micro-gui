# Micro-gui makefile
# Demonstrates building the library
# and the font/icon pipeline

lib:
	mkdir -p build; cd build; cmake .. && make; cd ..

all: icons fonts lib

icons: icons_1x icons_2x icons_4x icons_6x icons_8x

fonts: roboto_16 roboto_18 roboto_24 roboto_32

clean:
	rm -rf build/*

icons_1x: ./ugui/icons/icons_1x.h ./source/icons/icons_1x.c
	python3 ./scripts/build-iconic.py --scale=1 --folder=./resources/open-iconic/png --template=./scripts/icon-template.h --output=./ugui/icons/icons_1x.h
	python3 ./scripts/build-iconic.py --scale=1 --folder=./resources/open-iconic/png --template=./scripts/icon-template.c --output=./source/icons/icons_1x.c

icons_2x:
	python3 ./scripts/build-iconic.py --scale=2 --folder=./resources/open-iconic/png --template=./scripts/icon-template.h --output=./ugui/icons/icons_2x.h
	python3 ./scripts/build-iconic.py --scale=2 --folder=./resources/open-iconic/png --template=./scripts/icon-template.c --output=./source/icons/icons_2x.c

icons_4x:
	python3 ./scripts/build-iconic.py --scale=4 --folder=./resources/open-iconic/png --template=./scripts/icon-template.h --output=./ugui/icons/icons_4x.h
	python3 ./scripts/build-iconic.py --scale=4 --folder=./resources/open-iconic/png --template=./scripts/icon-template.c --output=./source/icons/icons_4x.c

icons_6x:
	python3 ./scripts/build-iconic.py --scale=6 --folder=./resources/open-iconic/png --template=./scripts/icon-template.h --output=./ugui/icons/icons_6x.h
	python3 ./scripts/build-iconic.py --scale=6 --folder=./resources/open-iconic/png --template=./scripts/icon-template.c --output=./source/icons/icons_6x.c

icons_8x:
	python3 ./scripts/build-iconic.py --scale=8 --folder=./resources/open-iconic/png --template=./scripts/icon-template.h --output=./ugui/icons/icons_8x.h
	python3 ./scripts/build-iconic.py --scale=8 --folder=./resources/open-iconic/png --template=./scripts/icon-template.c --output=./source/icons/icons_8x.c

roboto_16:
	python3 ./scripts/build-font.py --size=16 --font=./resources/fonts/RobotoMono-Regular.ttf --template=./scripts/font-template.c --output=./source/fonts/robotomono_regular_16.c
	python3 ./scripts/build-font.py --size=16 --font=./resources/fonts/RobotoMono-Regular.ttf --template=./scripts/font-template.h --output=./ugui/fonts/robotomono_regular_16.h

roboto_18:
	python3 ./scripts/build-font.py --size=18 --font=./resources/fonts/RobotoMono-Regular.ttf --template=./scripts/font-template.c --output=./source/fonts/robotomono_regular_18.c
	python3 ./scripts/build-font.py --size=18 --font=./resources/fonts/RobotoMono-Regular.ttf --template=./scripts/font-template.h --output=./ugui/fonts/robotomono_regular_18.h

roboto_24:
	python3 ./scripts/build-font.py --size=24 --font=./resources/fonts/RobotoMono-Regular.ttf --template=./scripts/font-template.c --output=./source/fonts/robotomono_regular_24.c
	python3 ./scripts/build-font.py --size=24 --font=./resources/fonts/RobotoMono-Regular.ttf --template=./scripts/font-template.h --output=./ugui/fonts/robotomono_regular_24.h

roboto_32:
	python3 ./scripts/build-font.py --size=32 --font=./resources/fonts/RobotoMono-Regular.ttf --template=./scripts/font-template.c --output=./source/fonts/robotomono_regular_32.c
	python3 ./scripts/build-font.py --size=32 --font=./resources/fonts/RobotoMono-Regular.ttf --template=./scripts/font-template.h --output=./ugui/fonts/robotomono_regular_32.h